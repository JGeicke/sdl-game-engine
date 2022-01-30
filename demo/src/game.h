#pragma once
#include <gameengine.h>
#include <ctime>
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

	void onZombieDeath(Health* healthComponent);

	void onWizardDeath(Health* healthComponent);

	void spawnPlayerProjectile();

	void spawnBossProjectiles();

	void addEnemyZombie(SDL_Point pos, int health);

	void addEnemyWolf(SDL_Point pos, int health);

	void addEnemyWizard(SDL_Point pos, int health);

	void addPlayer(SDL_Point pos);

	void setMasterVolume(float vol);

	void setSoundVolume(float vol);

	void setMusicVolume(float vol);

	void toggleSettings();

	void initWinterScene();

	void initWinterLakeScene();

	void initWinterRiverScene();

	void initWinterRoadScene();

	void initWinterEndScene();

	void initStartScene();

	void initGameOverScene();

	void initWinningScene();

	void nextLevel();

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

	size_t levelCompletedCounter = 0;
	int lastSceneIdx = -1;

	Entity player = { 0 };

	Entity bossRoomBlock = { 0 };
	size_t hpBarIndex = SIZE_MAX;

	Entity boss = { 0 };
	Entity bossDestinations[7];
	size_t bossDestinationIndex = 0;
	size_t lastBossDestinationIndex = 0;

	size_t enemyCount = 0;

	std::vector<size_t> settingSliders = {};
	std::vector<size_t> settingLabels = {};
	size_t settingPanel = 0;
	size_t settingButton = 0;
	size_t settingQuitGameButton = 0;

	bool hasSettings = false;
	bool isSettingsOpen = false;
};