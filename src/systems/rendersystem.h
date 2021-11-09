#pragma once
#include "gamesystem.h"
#include "SDL_image.h"
#include "../componentmanager.h"
#include "../components/components.h"
#include "../util/fileloader.h"
#include "../util/tilemap.h"
/**
 * @brief Render System to render objects and tilemaps in game world.
*/
class RenderSystem : GameSystem {
public:
	/**
	 * @brief Constructor for RenderSystem objects.
	 * @param spriteManager - Sprite manager for sprite objects.
	 * @param positionManager  - Position manager for position objects.
	 * @param renderer - SDL_Renderer for the actual rendering of the sprites in the gameworld.
	*/
	RenderSystem(ComponentManager<Sprite>* spriteManager, ComponentManager<Position>* positionManager, SDL_Renderer* renderer);
	/**
	 * @brief Render system update loop.
	*/
	virtual void update();

	void setMap(const char* tilesetPath, const char* tilemapPath, size_t layerCount);
private:
	/**
	 * @brief Reference to the sprite manager.
	*/
	ComponentManager<Sprite>* spriteManager;
	/**
	 * @brief Reference to the position manager.
	*/
	ComponentManager<Position>* positionManager;
	/**
	 * @brief Reference to the SDL_Renderer.
	*/
	SDL_Renderer* renderer;

	Tilemap* tilemap;
	
	Tileset* tileset;

	/**
	 * @brief Draw the given sprite in the gameworld.
	 * @param sprite - sprite to draw
	*/
	void draw(Sprite* sprite);

	/**
	 * @brief Renders the tilemap.
	*/
	void renderTilemap();

	void setTilesetSrcRectPosition(unsigned int tilemapData, unsigned int tileWidth, unsigned int tileHeight, unsigned int maxWidth);

	void setTilesetDestRectPosition(unsigned int currentX, unsigned int currentY, unsigned int maxWidth, unsigned int tileWidth, unsigned int tileHeight);

	/**
	 * @brief Render the textures of the renderer.
	*/
	void render();
};