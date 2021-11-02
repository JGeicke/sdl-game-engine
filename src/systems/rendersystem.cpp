#include "rendersystem.h"
RenderSystem::RenderSystem(ComponentManager<Sprite>* spriteManager, ComponentManager<Position>* positionManager, SDL_Renderer* renderer) {
	this->positionManager = positionManager;
	this->spriteManager = spriteManager;
	this->renderer = renderer;
}

void RenderSystem::update() {
	// clear renderer
	SDL_RenderClear(renderer);

	unsigned int index = spriteManager->getComponentCount();
	for (size_t i = 0; i < index; i++)
	{
		Sprite* sprite = spriteManager->getComponentWithIndex(i);
		Entity spriteEntity = sprite->getEntity();
		Position* spritePosition = positionManager->getComponent(spriteEntity);
		sprite->setDestinationRectPosition(spritePosition->x, spritePosition->y);
		draw(sprite);
	}
	render();
}

void RenderSystem::draw(Sprite* sprite) {
	// if sprite has no texture
	if (!sprite->hasTexture()) {
		// create texture
		SDL_Surface* tempSurface = IMG_Load(sprite->texturePath);
		SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		// cleanup surface
		SDL_FreeSurface(tempSurface);

		// set texture of sprite
		sprite->setTexture(spriteTexture);
	}
	SDL_RenderCopy(renderer, sprite->getTexture(), NULL, sprite->getDestinationRect());
}

void RenderSystem::render() {
	SDL_RenderPresent(renderer);
}