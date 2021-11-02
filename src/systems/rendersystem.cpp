#include "rendersystem.h"
/**
* @brief Constructor for RenderSystem objects to set needed references.
* @param spriteManager - Reference to the sprite manager for sprite objects.
* @param positionManager  - Reference to the position manager for position objects.
* @param renderer - Reference to the SDL_Renderer for the actual rendering of the sprites in the gameworld.
*/
RenderSystem::RenderSystem(ComponentManager<Sprite>* spriteManager, ComponentManager<Position>* positionManager, SDL_Renderer* renderer) {
	this->positionManager = positionManager;
	this->spriteManager = spriteManager;
	this->renderer = renderer;
}

/**
* @brief Render system update loop. Iterates over every sprite object and renders the texture to the position of the entity holding the sprite.	
*/
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
/**
 * @brief Checks if the sprite has a texture and creates a texture if it has not. Afterwards adds the sprite to the renderer to render.
 * @param sprite 
*/
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

/**
 * @brief Render the current textures of the renderer.
*/
void RenderSystem::render() {
	SDL_RenderPresent(renderer);
}