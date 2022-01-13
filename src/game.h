#pragma once
#include "gameengine.h"
class Game {
public:
	void init();
	void start();

	void playerProjectileHandler(Collider* a, Collider* b);

	void enemyProjectileHandler(Collider* a, Collider* b);

	void enemyCollisionHandler(Collider* a, Collider* b);

	void onBossRoomEnter(Collider* a, Collider* b);

	bool onBossReachingDestination(EnemyMovement* mov);

	void portalHandler(Collider* a, Collider* b);

	void onPlayerDeath(Health* healthComponent);

	void onWolfDeath(Health* healthComponent);

	void onWizardDeath(Health* healthComponent);

	void spawnPlayerProjectile();

	void spawnBossProjectiles();

	void addEnemyWolf(SDL_Point pos, int health);

	void addEnemyWizard(SDL_Point pos, int health);

	void initWinterScene();

	void initWinterEndScene();

	void initStartScene();

	void initGameOverScene();

	void initWinningScene();

	void startGame();

	void restartGame();

	void gameOver();

	void wonGame();

	void quitGame();
private:
	void initGameplayUI(UIManager* uiManager);

	GameEngine* gameEngine = nullptr;
	UIManager* uiManager = nullptr;;
	InputManager* inputManager = nullptr;

	Entity player = { 0 };

	Entity bossRoomBlock = { 0 };
	size_t hpBarIndex = SIZE_MAX;

	Entity boss = { 0 };
	Entity bossDestinations[3];
	size_t bossDestinationIndex = 0;

	size_t enemyCount = 0;
};