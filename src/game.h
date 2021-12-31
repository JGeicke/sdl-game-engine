#pragma once
#include "gameengine.h"
class Game {
public:
	void init();
	void start();

	void enemyProjectileHandler(Collider* a, Collider* b);

	void enemyCollisionHandler(Collider* a, Collider* b);

	void onPlayerDeath(Health* healthComponent);

	void spawnPlayerProjectile();

	void addEnemyWolf(SDL_Point pos);

	void initWinterScene();

	void initStartScene();

	void startGame();

	void quitGame();
private:
	void initGameplayUI(UIManager* uiManager);

	GameEngine* gameEngine = nullptr;
	UIManager* uiManager = nullptr;;
	InputManager* inputManager = nullptr;

	Entity player = { 0 };
	size_t hpBarIndex = SIZE_MAX;
};