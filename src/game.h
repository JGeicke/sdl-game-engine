#pragma once
#include "gameengine.h"
class Game {
public:
	void init();
	void start();

	void enemyCollisionHandler(Collider* a, Collider* b);
private:
	void initUI(UIManager* uiManager);

	GameEngine* gameEngine;
	UIManager* uiManager;

	Entity player;
	size_t hpBarIndex = SIZE_MAX;
};