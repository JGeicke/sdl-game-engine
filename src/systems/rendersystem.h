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
	RenderSystem(ComponentManager<Sprite>* spriteManager, ComponentManager<Position>* positionManager, SDL_Renderer* renderer, ComponentManager<CameraFollow>* cameraFollowManager);
	/**
	 * @brief Render system update loop.
	*/
	virtual void update();

	/**
	 * @brief Sets the current tilemap to display.
	 * @param tilesetPath - Path to tileset image used by tilemap.
	 * @param tilemapPath - Path to tilemap json file generated by tiled.
	 * @param layerCount - Count of layers in tilemap.
	*/
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
	 * @brief Reference to the camera follow manager.
	*/
	ComponentManager<CameraFollow>* cameraFollowManager;

	/**
	 * @brief Reference to the SDL_Renderer.
	*/
	SDL_Renderer* renderer;

	/**
	 * @brief Reference to the current tilemap.
	*/
	Tilemap* tilemap;
	
	/**
	 * @brief Reference to the current tileset used by the tilemap.
	*/
	Tileset* tileset;

	/**
	 * @brief View area rectangle of the camera.
	*/
	SDL_Rect camera;

	/**
	 * @brief Renders all current sprites in the window.
	*/
	void renderSprites();

	/**
	 * @brief Draw the given sprite in the gameworld.
	 * @param sprite - sprite to draw
	*/
	void draw(Sprite* sprite);

	/**
	 * @brief Renders the tilemap.
	*/
	void renderTilemap();

	/**
	 * @brief Sets the source rectangle of the tileset to display the right part of the tileset.
	 * @param tilemapData - What tile to display based on the tilemap.
	 * @param tileWidth - Width of the tiles.
	 * @param tileHeight - Height of the tiles.
	*/
	void setTilesetSrcRectPosition(unsigned int tilemapData, unsigned int tileWidth, unsigned int tileHeight);

	/**
	 * @brief Sets the destination rectangle of the tileset to display the tiles in the right area.
	 * @param currentX - Current X position on the tilemap.
	 * @param currentY - Current Y position on the tilemap.
	 * @param maxTilesPerRow - Maxixum tiles per row on the tilemap.
	 * @param tileWidth - Width of the tiles.
	 * @param tileHeight - Height of the tiles.
	*/
	void setTilesetDestRectPosition(unsigned int currentX, unsigned int currentY, unsigned int maxTilesPerRow, unsigned int tileWidth, unsigned int tileHeight);

	/**
	 * @brief Render the textures of the renderer.
	*/
	void render();

	/**
	 * @brief Moves the camera to the entity with the follow camera component.
	*/
	void moveCamera();
};