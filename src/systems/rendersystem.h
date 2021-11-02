#pragma once
#include "gamesystem.h"
#include "SDL_image.h"
#include "../componentmanager.h"
#include "../components/components.h"
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

	/**
	 * @brief Draw the given sprite in the gameworld.
	 * @param sprite - sprite to draw
	*/
	void draw(Sprite* sprite);

	/**
	 * @brief Render the textures of the renderer.
	*/
	void render();
};