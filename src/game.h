#pragma once
#include "gameengine.h"
class Game {
public:
	void init();
	void start();

	void enemyProjectileHandler(Collider* a, Collider* b);

	void enemyCollisionHandler(Collider* a, Collider* b);

	void onPlayerDeath(Health* healthComponent);

	void initWinterScene();

	void initStartScene();

	void startGame();

	void quitGame();
private:
	void initGameplayUI(UIManager* uiManager);

	GameEngine* gameEngine;
	UIManager* uiManager;

	Entity player;
	size_t hpBarIndex = SIZE_MAX;
};