#pragma once
#include "gamesystem.h"
#include "SDL_image.h"
#include "../componentmanager.h"
#include "../components/components.h"
class RenderSystem : GameSystem {
public:
	RenderSystem(ComponentManager<Sprite>* spriteManager, ComponentManager<Position>* positionManager, SDL_Renderer* renderer);
	virtual void update();
private:
	ComponentManager<Sprite>* spriteManager;
	ComponentManager<Position>* positionManager;
	SDL_Renderer* renderer;

	void draw(Sprite* sprite);

	void render();
};