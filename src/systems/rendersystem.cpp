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

	renderTilemap();

	// TODO: adjust render position
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

void RenderSystem::setMap(const char* tilesetPath, const char* tilemapPath, size_t layerCount) {
	SDL_Point size;
	tilemap = FileLoader::loadTilemap(tilemapPath, layerCount);

	// create texture
	SDL_Surface* tempSurface = IMG_Load(tilesetPath);
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	// get tileset width/height
	SDL_QueryTexture(tempTexture, NULL, NULL, &size.x, &size.y);

	tileset = new Tileset(tempTexture, size.x, size.y);

	// set srcRect
	tileset->initSourceRect(tilemap->getTileWidth(), tilemap->getTileHeight());

	// set destRect
	tileset->initDestinationRect(tilemap->getTileWidth(), tilemap->getTileHeight());

	// cleanup surface
	SDL_FreeSurface(tempSurface);
}

void RenderSystem::renderTilemap() {
	unsigned int tileWidth, tileHeight, currentDestX, currentDestY, maxMapWidth, maxMapHeight;
	currentDestX = 0;
	currentDestY = 0;
	maxMapWidth = tilemap->getMapWidth();
	maxMapHeight = tilemap->getMapHeight();
	tileWidth = tilemap->getTileWidth();
	tileHeight = tilemap->getTileHeight();
	size_t layers = tilemap->getLayerCount();

	for (size_t i = 0; i < layers; i++)
	{
		std::vector<unsigned int> layer = tilemap->getLayer(i);
		for (size_t i = 0; i < layer.size(); i++)
		{
			if (currentDestX >= maxMapWidth) {
				currentDestX = 0;
				currentDestY = currentDestY + 1;
			}

			// check if spot is empty
			if (layer[i] != 0) {
				// calculate part to render
				setTilesetSrcRectPosition(layer[i], tileWidth, tileHeight, maxMapWidth);

				// calculate part to render at ingame
				setTilesetDestRectPosition(currentDestX, currentDestY, maxMapWidth, tileWidth, tileHeight);
				SDL_RenderCopy(renderer, tileset->getTexture(), tileset->getSourceRect(), tileset->getDestinationRect());
			}
			currentDestX = currentDestX + 1;
		}
		currentDestX = 0;
		currentDestY = 0;
	}
}

void RenderSystem::setTilesetSrcRectPosition(unsigned int tilemapData, unsigned int tileWidth, unsigned int tileHeight, unsigned int maxWidth) {
	unsigned int tilesetWidth = tileset->getTilesetWidth();

	unsigned int newX;
	unsigned int newY;
	// check if first row tileWidth * maxWidth
	if ((tilemapData * tileWidth) <= (tilesetWidth)) {
		newX = (tilemapData == 0) ? tilemapData * tileWidth : (tilemapData - 1) * tileWidth;
		newY = 0;
	}
	else {
		// calculate row
		unsigned int yoffset = (tilemapData * tileWidth) / (tilesetWidth);
		unsigned int xoffset = ((tilemapData * tileWidth) % (tilesetWidth)) / tileWidth;

		newX = (xoffset == 0) ? xoffset * tileWidth : (xoffset - 1) * tileWidth;
		newY = yoffset * tileHeight;
	}
	// set source rect position
	tileset->setSourceRect(newX, newY);
}

void RenderSystem::setTilesetDestRectPosition(unsigned int currentX, unsigned int currentY, unsigned int maxWidth, unsigned int tileWidth, unsigned int tileHeight) {
	unsigned int newX;
	unsigned int newY;

	if (currentX < maxWidth) {
		newX = (currentX == 0) ? currentX * tileWidth : (currentX - 1) * tileWidth;
		newY = (currentY == 0) ? currentY * tileHeight : (currentY - 1) * tileHeight;
	}
	else {
		// set new position
		newX = (currentX == 0) ? currentX * tileWidth : (currentX - 1) * tileWidth;
		newY = (currentY == 0) ? currentY * tileHeight : (currentY - 1) * tileHeight;
	}
	// set destination rect position
	tileset->setDestinationRect(newX, newY);
}