#include "gameengine.h"
#include "game.h"

enum FONTS {
	NORMAL,
	PIXELTITLE,
	PIXELSUBTITLE,
	SMALL
};

Game* game = nullptr;

#pragma region Wrapper
void onBossRoomEnterWrapper(Collider* a, Collider* b) {
	game->onBossRoomEnter(a, b);
}

void enemyProjectileWrapper(Collider* a, Collider* b) {
	game->enemyProjectileHandler(a, b);
}

void playerProjectileWrapper(Collider* a, Collider* b) {
	game->playerProjectileHandler(a, b);
}

void portalWrapper(Collider* a, Collider* b) {
	game->portalHandler(a, b);
}

void enemyCollisionWrapper(Collider* a, Collider* b) {
	game->enemyCollisionHandler(a,b);
}

void onPlayerDeathWrapper(Health* healthComponent) {
	game->onPlayerDeath(healthComponent);
}

bool onBossReachingDestinationWrapper(EnemyMovement* mov) {
	return game->onBossReachingDestination(mov);
}

void onWolfDeathWrapper(Health* healthComponent) {
	game->onWolfDeath(healthComponent);
}

void onZombieDeathWrapper(Health* healthComponent) {
	game->onZombieDeath(healthComponent);
}

void onWizardDeathWrapper(Health* healthComponent) {
	game->onWizardDeath(healthComponent);
}

void initStartSceneWrapper() {
	game->initStartScene();
}

void quitGameWrapper() {
	game->quitGame();
}

void initWinningSceneWrapper() {
	game->initWinningScene();
}

void startGameWrapper() {
	game->startGame();
}

void restartGameWrapper() {
	game->restartGame();
}

void initWinterSceneWrapper() {
	game->initWinterScene();
}

void initWinterLakeSceneWrapper() {
	game->initWinterLakeScene();
}

void initWinterRiverSceneWrapper() {
	game->initWinterRiverScene();
}

void initWinterRoadSceneWrapper() {
	game->initWinterRoadScene();
}

void initWinterEndSceneWrapper() {
	game->initWinterEndScene();
}

void initGameOverSceneWrapper() {
	game->initGameOverScene();
}

void toggleSettingsWrapper() {
	game->toggleSettings();
}


void spawnPlayerProjectileWrapper() {
	game->spawnPlayerProjectile();
}

void setMasterVolumeWrapper(float vol) {
	game->setMasterVolume(vol);
}

void setMusicVolumeWrapper(float vol) {
	game->setMusicVolume(vol);
}

void setSoundVolumeWrapper(float vol) {
	game->setSoundVolume(vol);
}
#pragma endregion Wrapper

#pragma region Settings
void Game::setMasterVolume(float vol) {
	this->gameEngine->setMasterVolume(vol);
}

void Game::setSoundVolume(float vol) {
	this->gameEngine->setSoundVolume(vol);
}

void Game::setMusicVolume(float vol) {
	this->gameEngine->setMusicVolume(vol);
}

void Game::toggleSettings() {
	if (!hasSettings) return;

	isSettingsOpen = !isSettingsOpen;

	for (size_t i = 0; i < settingSliders.size(); i++)
	{
		Slider* nextSlider = uiManager->getSlider(i);
		nextSlider->show(!nextSlider->isVisible());
	}

	for (size_t i = 0; i < settingLabels.size(); i++)
	{
		Label* nextLabel = uiManager->getLabel(i);
		nextLabel->show(!nextLabel->isVisible());
	}

	Panel* p = uiManager->getPanel(settingPanel);
	p->show(!p->isVisible());

	Button* b = uiManager->getButton(settingButton);
	b->show(!b->isVisible());
}
#pragma endregion Settings

#pragma region Handler
void Game::onBossRoomEnter(Collider* a, Collider* b) {
	if (b->getEntity().tag == "player") {
		// do stuff
		Collider* bossRoomBlockCollider = this->gameEngine->getColliderComponent(this->bossRoomBlock);
		bossRoomBlockCollider->setActive(true);
		this->gameEngine->setBGM("../TestTextures/boss_theme.mp3");
	}
}

void Game::enemyCollisionHandler(Collider* a, Collider* b) {
	int enemyAtk = 100;

	if (b->getEntity().tag == "player") {
		UIManager* uimanager = this->gameEngine->getUIManager();
		Health* playerHealth = this->gameEngine->getHealthComponent(this->player);
		int currHealth = playerHealth->getCurrentHealth();
		playerHealth->takeDamage(enemyAtk);

		if (currHealth - enemyAtk > 0) {
			//update ui
			uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());
		}

		playerHealth->print();
	}

}

void Game::enemyProjectileHandler(Collider* a, Collider* b) {
	int enemyAtk = 35;
	if (b->getEntity().tag == "player") {
		/*
		ComponentManager<Health>* manager = this->gameEngine->getHealthManager();
		UIManager* uimanager = this->gameEngine->getUIManager();
		Health* playerHealth = manager->getComponent(this->player);

		//update ui
		uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());

		// delete projectile
		Entity e = a->getEntity();
		this->gameEngine->destroyProjectile(e);
		b->resetLastCollision();

		playerHealth->takeDamage(25);
		*/
		UIManager* uimanager = this->gameEngine->getUIManager();
		Health* playerHealth = this->gameEngine->getHealthComponent(this->player);
		int currHealth = playerHealth->getCurrentHealth();

		//destroy projectile
		this->gameEngine->destroyProjectile(a->getEntity());

		playerHealth->takeDamage(35);

		if (currHealth - enemyAtk > 0) {
			//update ui
			uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());
		}
	}
}

void Game::playerProjectileHandler(Collider* a, Collider* b) {
	if (b->getEntity().tag == "enemy") {
		Health* enemyHealth = gameEngine->getHealthComponent(b->getEntity());
	
		// delete projectile
		Entity e = a->getEntity();
		this->gameEngine->destroyProjectile(e);

		enemyHealth->takeDamage(25);

		if (enemyHealth->getCurrentHealth() > 0) {
			this->gameEngine->playAudioClip(b->getEntity(), 0);
		}
	}
}

void Game::portalHandler(Collider* a, Collider* b) {
	if (b->getEntity().tag == "player" && this->enemyCount == 0) {
		this->levelCompletedCounter++;

		if (this->levelCompletedCounter == 2) {
			Scene* end = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter_lake.json", 4, nullptr, &initWinterEndSceneWrapper);
			this->gameEngine->changeScene(end, false);
		}
		else {
			this->nextLevel();
		}
	}
}

void Game::onPlayerDeath(Health* healthComponent) {
	this->gameOver();
}

void Game::onWolfDeath(Health* healthComponent) {
	this->gameEngine->playAudioClip(healthComponent->getEntity(), 1);
	this->gameEngine->destroyEntity(healthComponent->getEntity());
	enemyCount--;
}

void Game::onZombieDeath(Health* healthComponent) {
	//this->gameEngine->playAudioClip(healthComponent->getEntity(), 1);
	this->gameEngine->destroyEntity(healthComponent->getEntity());
	enemyCount--;
}

void Game::onWizardDeath(Health* healthComponent) {
	enemyCount--;
	this->wonGame();
}

bool Game::onBossReachingDestination(EnemyMovement* mov) {
	if (mov != nullptr) {
		this->spawnBossProjectiles();
		this->gameEngine->setEnemyDestination(this->boss, this->gameEngine->getPositionComponent(this->bossDestinations[bossDestinationIndex]));
		bossDestinationIndex++;

		if (bossDestinationIndex == 3) {
			bossDestinationIndex = 0;
		}
		return true;
	}
	return false;
}
#pragma endregion Handler

#pragma region Projectiles
void Game::spawnBossProjectiles() {
	Position* bossPosition = gameEngine->getPositionComponent(this->boss);
	if (bossPosition != nullptr) {

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (y == 0 && x == 0) continue;
				Entity e = this->gameEngine->createProjectile("../TestTextures/boss_proj.png", { 6,6 }, 2.0f, { bossPosition->x(), bossPosition->y() }, { bossPosition->x() + x, bossPosition->y()+y }, 3.0f, false);
				Collider* col = this->gameEngine->getColliderComponent(e);
				col->onTriggerEnter(&enemyProjectileWrapper);
			}
		}
	}
}

void Game::spawnPlayerProjectile() {
	//disable when setting open
	if (isSettingsOpen) return;

	Position* playerPosition = gameEngine->getPositionComponent(this->player);
	if (playerPosition != nullptr) {
		Entity e = this->gameEngine->createProjectile("../TestTextures/proj.png", { 6,6 }, 2.0f, { playerPosition->x(), playerPosition->y() }, this->inputManager->getMousePosition(), 5.0f, true);
		Collider* col = this->gameEngine->getColliderComponent(e);
		col->onTriggerEnter(&playerProjectileWrapper);
	}
}
#pragma endregion Projectiles

#pragma region Enemies
void Game::addEnemyWolf(SDL_Point pos, int health) {
	Entity wolf = gameEngine->addEntity("enemy", false, pos);
	gameEngine->addSpriteComponent(wolf, "../TestTextures/wolf_idle_side.png", { 32, 32 }, 2.0f);
	Collider* wolfCollider = gameEngine->addColliderComponent(wolf, { 0, 0 }, { 32, 32 }, false);
	wolfCollider->onCollisionEnter(&enemyCollisionWrapper);
	gameEngine->addAnimatorComponent(wolf);
	gameEngine->addAnimation(wolf, STATES::IDLE_SIDE, 1, 150, "../TestTextures/wolf_idle_side.png");
	gameEngine->addAnimation(wolf, STATES::WALK_SIDE, 3, 150, "../TestTextures/wolf_walk_side.png");
	gameEngine->addAnimation(wolf, STATES::IDLE_UP, 1, 150, "../TestTextures/wolf_idle_up.png");
	gameEngine->addAnimation(wolf, STATES::WALK_UP, 3, 150, "../TestTextures/wolf_walk_up.png");
	gameEngine->addAnimation(wolf, STATES::IDLE_DOWN, 1, 150, "../TestTextures/wolf_idle_down.png");
	gameEngine->addAnimation(wolf, STATES::WALK_DOWN, 3, 150, "../TestTextures/wolf_walk_down.png");

	EnemyMovement* mov = gameEngine->addEnemyMovementComponent(wolf, 2.5, player);
	mov->setMaxDistance(20);

	Health* healthComponent = gameEngine->addHealthComponent(wolf, health);
	healthComponent->onZeroHealth(&onWolfDeathWrapper);

	gameEngine->addAudioComponent(wolf);
	gameEngine->addAudioClip(wolf, "../TestTextures/hit.mp3");
	gameEngine->addAudioClip(wolf, "../TestTextures/uff.mp3");

	this->enemyCount++;
}

void Game::addEnemyWizard(SDL_Point pos, int health) {
	Entity wizard = gameEngine->addEntity("enemy", false, pos);
	gameEngine->addSpriteComponent(wizard, "../TestTextures/wizard_idle.png", {64,64}, 1.0f);
	Collider* wizardCollider = gameEngine->addColliderComponent(wizard, { 0, 0 }, { 64, 64 }, false);

	Animator* anim = gameEngine->addAnimatorComponent(wizard);
	gameEngine->addAnimation(wizard, STATES::IDLE_SIDE, 10, 150, "../TestTextures/wizard_idle.png");
	gameEngine->addAnimation(wizard, STATES::WALK_SIDE, 10, 150, "../TestTextures/wizard_idle.png");
	gameEngine->addAnimation(wizard, STATES::IDLE_UP, 10, 150, "../TestTextures/wizard_idle.png");
	gameEngine->addAnimation(wizard, STATES::WALK_UP, 10, 150, "../TestTextures/wizard_idle.png");
	gameEngine->addAnimation(wizard, STATES::IDLE_DOWN, 10, 150, "../TestTextures/wizard_idle.png");
	gameEngine->addAnimation(wizard, STATES::WALK_DOWN, 10, 150, "../TestTextures/wizard_idle.png");

	gameEngine->addEnemyMovementComponent(wizard, 2.0f);

	Health* healthComponent = gameEngine->addHealthComponent(wizard, health);
	healthComponent->onZeroHealth(&onWizardDeathWrapper);

	this->enemyCount++;

	this->boss = wizard;
}

void Game::addEnemyZombie(SDL_Point pos, int health) {
	Entity zombie = gameEngine->addEntity("enemy", false, pos);
	gameEngine->addSpriteComponent(zombie, "../TestTextures/zombie_idle_down.png", { 64,64 }, 1.5f);
	Collider* collider = gameEngine->addColliderComponent(zombie, { 0, 0 }, { 32, 46 }, false);
	collider->onCollisionEnter(&enemyCollisionWrapper);

	Animator* anim = gameEngine->addAnimatorComponent(zombie);
	gameEngine->addAnimation(zombie, STATES::IDLE_SIDE, 5, 160, "../TestTextures/zombie_idle_side.png");
	gameEngine->addAnimation(zombie, STATES::WALK_SIDE, 6, 100, "../TestTextures/zombie_walk_side.png");
	gameEngine->addAnimation(zombie, STATES::IDLE_UP, 5, 160, "../TestTextures/zombie_idle_up.png");
	gameEngine->addAnimation(zombie, STATES::WALK_UP, 6, 100, "../TestTextures/zombie_walk_up.png");
	gameEngine->addAnimation(zombie, STATES::IDLE_DOWN, 5, 160, "../TestTextures/zombie_idle_down.png");
	gameEngine->addAnimation(zombie, STATES::WALK_DOWN, 6, 100, "../TestTextures/zombie_walk_down.png");

	EnemyMovement* mov = gameEngine->addEnemyMovementComponent(zombie, 1.5, player);
	mov->setMaxDistance(20);

	Health* healthComponent = gameEngine->addHealthComponent(zombie, health);
	healthComponent->onZeroHealth(&onZombieDeathWrapper);
	this->enemyCount++;
}
#pragma endregion Enemies

#pragma region Player
void Game::addPlayer(SDL_Point pos) {
	if (this->player.uid == 0) {
		this->player = gameEngine->addPlayer("player", true, { pos.x, pos.y }, 5);
		gameEngine->addSpriteComponent(player, "../TestTextures/char_idle_side.png", { 64, 64 }, 1.5f);
		gameEngine->setCameraFollowTarget(player);

		Animator* playerAnimator = gameEngine->addAnimatorComponent(player);
		gameEngine->addAnimation(player, STATES::IDLE_SIDE, 5, 160, "../TestTextures/char_idle_side.png");
		gameEngine->addAnimation(player, STATES::WALK_SIDE, 6, 100, "../TestTextures/char_walk_side.png");
		gameEngine->addAnimation(player, STATES::IDLE_UP, 5, 160, "../TestTextures/char_idle_up.png");
		gameEngine->addAnimation(player, STATES::WALK_UP, 6, 100, "../TestTextures/char_walk_up.png");
		gameEngine->addAnimation(player, STATES::IDLE_DOWN, 5, 160, "../TestTextures/char_idle_down.png");
		gameEngine->addAnimation(player, STATES::WALK_DOWN, 6, 100, "../TestTextures/char_walk_down.png");
		gameEngine->addAnimation(player, STATES::ATK_SIDE, 3, 180, "../TestTextures/char_atk_side.png");
		gameEngine->addAnimation(player, STATES::ATK_DOWN, 3, 180, "../TestTextures/char_atk_down.png");
		gameEngine->addAnimation(player, STATES::ATK_UP, 3, 180, "../TestTextures/char_atk_up.png");

		playerAnimator->markAnimationInterruptible(STATES::ATK_SIDE);
		playerAnimator->markAnimationInterruptible(STATES::ATK_DOWN);
		playerAnimator->markAnimationInterruptible(STATES::ATK_UP);

		Collider* playerCollider = gameEngine->addColliderComponent(player, { 0, 0 }, { 15, 46 }, false);
		Health* playerHealth = gameEngine->addHealthComponent(player, 100);
		playerHealth->onZeroHealth(&onPlayerDeathWrapper);
		this->uiManager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());
	}
	else {
		this->gameEngine->setPosition(this->player, pos);
	}
}
#pragma endregion Player

#pragma region Scenes
void Game::initStartScene() {
	unsigned int gameWindowWidth = this->gameEngine->getGameWindowWidth();
	unsigned int gameWindowHeight = this->gameEngine->getGameWindowHeight();
	SDL_Color white = { 255,255,255 };
	SDL_Color grey = { 48,48,48 };
	SDL_Color red = { 224, 40, 27 };
	SDL_Color buttonHover = { 77,77,77 };
	Entity bg = gameEngine->addEntity("", false, { (int)((gameWindowWidth / 2) / gameEngine->getCameraZoomFactorX()), (int)((gameWindowHeight / 2) / gameEngine->getCameraZoomFactorY()) });
	gameEngine->addSpriteComponent(bg, "../TestTextures/BG.png", { 1800,893 }, 1.0f);

	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2) - 180, "Risk of Snow", grey, FONTS::PIXELTITLE);
	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2) - 120, "Demo Game", red, FONTS::PIXELSUBTITLE);
	Button* startButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Start Game", white, grey, FONTS::NORMAL, { 10,5 }, buttonHover));
	startButton->onClick(&startGameWrapper);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2) + 65, "Quit", white, grey, FONTS::NORMAL, { 63,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initGameOverScene() {
	SDL_Color white = { 255,255,255 };
	SDL_Color grey = { 48,48,48 };
	SDL_Color buttonHover = { 77,77,77 };
	unsigned int gameWindowWidth = this->gameEngine->getGameWindowWidth();
	unsigned int gameWindowHeight = this->gameEngine->getGameWindowHeight();
	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2) - 180, "Game Over", white, 0);
	Button* startButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Try Again", white, grey, FONTS::NORMAL, { 10,5 }, buttonHover));
	startButton->onClick(&restartGameWrapper);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2) + 65, "Quit", white, grey, FONTS::NORMAL, { 48,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initWinningScene() {
	SDL_Color white = { 255,255,255 };
	SDL_Color grey = { 48,48,48 };
	SDL_Color buttonHover = { 77,77,77 };
	unsigned int gameWindowWidth = this->gameEngine->getGameWindowWidth();
	unsigned int gameWindowHeight = this->gameEngine->getGameWindowHeight();
	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2) - 180, "You won!", white, 0);
	//Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Quit", white, grey, 0, { 48,5 }, buttonHover));
	//quitButton->onClick(&quitGameWrapper);
	Button* startButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Play Again", white, grey, FONTS::NORMAL, { 10,5 }, buttonHover));
	startButton->onClick(&restartGameWrapper);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2) + 65, "Quit", white, grey, FONTS::NORMAL, { 54,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initWinterEndScene() {
	this->addPlayer({ 32 * 26, 32 * 25});
	//this->gameEngine->getPositionComponent(this->player)->setPosition(32 * 26*gameEngine->getCameraZoomFactorX(), 32 * 25*gameEngine->getCameraZoomFactorY());

	// add paths for boss
	this->bossDestinations[0] = this->gameEngine->addEntity("node", false, { 112, 464 });
	this->bossDestinations[1] = this->gameEngine->addEntity("node", false, { 464, 142 });
	this->bossDestinations[2] = this->gameEngine->addEntity("node", false, { 623, 687 });

	this->addEnemyWizard({ 330, 494 }, 500);

	EnemyMovement* enemyMov = this->gameEngine->getEnemyMovementComponent(this->boss);

	if (enemyMov != nullptr) {
		this->gameEngine->setEnemyDestination(this->boss, this->gameEngine->getPositionComponent(this->bossDestinations[bossDestinationIndex]));
		enemyMov->onReachingDestination(&onBossReachingDestinationWrapper);
		bossDestinationIndex++;
	}
	// add boss trigger
	Entity trigger = gameEngine->addEntity("trigger", false, { 705, 529});
	Collider* bossRoomTrigger = gameEngine->addColliderComponent(trigger, { 0,0 }, { 64, 96 }, true);
	bossRoomTrigger->onTriggerEnter(&onBossRoomEnterWrapper);

	this->bossRoomBlock = gameEngine->addEntity("", false, {783, 529});
	Collider* bossRoomBlockCollider = gameEngine->addColliderComponent(this->bossRoomBlock, { 0,0 }, { 32,96 }, false);
	bossRoomBlockCollider->setActive(false);
}

void Game::initWinterScene() {
	//player
	this->addPlayer({ 19 * 32, 14 * 32});

	// TODO: fix player collision with enemies (knockback etc.)
	//wolf
	this->addEnemyWolf({ 1040, 850 }, 300);

	//wolf2
	this->addEnemyWolf({ 840,850 }, 300);

	/* projectile test
	ComponentManager<ProjectileMovement>* man = gameEngine->getProjectileMovementManager();
	Entity proj = gameEngine->addEntity("projectile", false, { 1040, 850 });
	gameEngine->addSpriteComponent(proj, "../TestTextures/proj.png", {6,6}, 2.0f);
	Collider* projCollider = gameEngine->addColliderComponent(proj, { 0,0 }, { 12,12 }, true);
	projCollider->onTriggerEnter(&enemyProjectileWrapper);
	gameEngine->addProjectileMovement(proj, { 1040, 850 }, {840, 550}, 3);
	*/

	//portal
	Entity portal = gameEngine->addEntity("portal", false, {13*32+16,42*32 + 32});
	gameEngine->addSpriteComponent(portal, "../TestTextures/portal.png", { 32,64 }, 1.0f);
	Collider* col = gameEngine->addColliderComponent(portal, { 0,0 }, { 32,64 }, true);
	col->onTriggerEnter(&portalWrapper);
}

void Game::initWinterLakeScene() {
	this->addPlayer({21*32, 16*32});

	//enemy
	this->addEnemyWolf({ 17 * 32,29 * 32 }, 200);
	this->addEnemyWolf({ 23 * 32,35 * 32 }, 200);
	this->addEnemyWolf({ 36 * 32,33 * 32 }, 200);

	//portal
	Entity portal = gameEngine->addEntity("portal", false, { 9 * 32 + 16,40 * 32 + 32 });
	gameEngine->addSpriteComponent(portal, "../TestTextures/portal.png", { 32,64 }, 1.0f);
	Collider* col = gameEngine->addColliderComponent(portal, { 0,0 }, { 32,64 }, true);
	col->onTriggerEnter(&portalWrapper);
}

void Game::initWinterRiverScene() {
	this->addPlayer({ 42 * 32, 6 * 32 });

	// enemy
	this->addEnemyZombie({ 18*32, 37*32 }, 300);
	this->addEnemyZombie({ 12 * 32, 28 * 32 }, 300);

	// portal
	Entity portal = gameEngine->addEntity("portal", false, { 1 * 32 + 16,30 * 32 + 32 });
	gameEngine->addSpriteComponent(portal, "../TestTextures/portal.png", { 32,64 }, 1.0f);
	Collider* col = gameEngine->addColliderComponent(portal, { 0,0 }, { 32,64 }, true);
	col->onTriggerEnter(&portalWrapper);
}

void Game::initWinterRoadScene() {
	this->addPlayer({ 13 * 32, 42 * 32 });

	// enemy
	this->addEnemyZombie({ 27 * 32, 18 * 32 }, 300);
	this->addEnemyZombie({ 21 * 32, 12 * 32 }, 300);

	//portal
	Entity portal = gameEngine->addEntity("portal", false, { 46 * 32 + 16,15 * 32 + 32 });
	Sprite* portalSprite = gameEngine->addSpriteComponent(portal, "../TestTextures/portal.png", { 32,64 }, 1.0f);
	portalSprite->setTextureFlip(SDL_FLIP_HORIZONTAL);
	Collider* col = gameEngine->addColliderComponent(portal, { 0,0 }, { 32,64 }, true);
	col->onTriggerEnter(&portalWrapper);
}
#pragma endregion Scenes

void Game::startGame(){
	this->enemyCount = 0;
	this->levelCompletedCounter = 0;
	// clear start ui
	this->uiManager->clearUI();

	//Scene* first = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, nullptr, &initWinterSceneWrapper);
	//this->gameEngine->changeScene(first, false);
	initGameplayUI(this->uiManager);
	this->nextLevel();
	this->inputManager->addActionHandler(SDL_BUTTON_LEFT, &spawnPlayerProjectileWrapper);
}

void Game::restartGame() {
	this->player = { 0 };
	this->boss = { 0 };
	this->bossRoomBlock = { 0 };
	this->bossDestinationIndex = 0;
	this->enemyCount = 0;
	this->levelCompletedCounter = 0;
	// clear start ui
	this->uiManager->clearUI();
	this->settingSliders = {};
	this->settingLabels = {};

	//Scene* first = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, "../TestTextures/new_bgm.mp3", &initWinterSceneWrapper);
	//this->gameEngine->changeScene(first, false);
	initGameplayUI(this->uiManager);
	this->nextLevel();
	this->inputManager->addActionHandler(SDL_BUTTON_LEFT, &spawnPlayerProjectileWrapper);
}

void Game::gameOver() {
	hasSettings = false;
	this->player = { 0 };
	// clear start ui
	this->uiManager->clearUI();

	// start screen
	Scene* gameOver = new Scene("../TestTextures/game_over_tileset.png", "../TestTextures/game_over.json", 1, "../TestTextures/game_over.mp3", &initGameOverSceneWrapper);
	this->gameEngine->changeScene(gameOver, true);
}

void Game::wonGame() {
	hasSettings = false;
	// clear start ui
	this->uiManager->clearUI();

	// start screen
	Scene* won = new Scene("../TestTextures/game_over_tileset.png", "../TestTextures/game_over.json", 1, "../TestTextures/win.mp3", &initWinningSceneWrapper);
	this->gameEngine->changeScene(won, true);
}

void Game::quitGame(){
	this->gameEngine->quit();
}

void Game::initGameplayUI(UIManager* uiManager) {
	// UI
	SDL_Color grey = { 48,48,48 };
	SDL_Color lightGrey = { 89,89,89 };
	SDL_Color textColor = { 255,255,255 };
	SDL_Color slider = { 77,77,77 };
	SDL_Color buttonHover = {106,106,106};

	size_t progIndex = uiManager->addProgressBar(15, 65, 250, 20, grey, { 44, 135, 22 });
	uiManager->getProgressBar(progIndex)->setProgress(0.4f);
	this->hpBarIndex = progIndex;

	// Create setting ui elements
	this->isSettingsOpen = true;
	this->hasSettings = true;

	this->settingPanel = uiManager->addPanel((int)this->gameEngine->getGameWindowWidth() / 2 - 125, (int)this->gameEngine->getGameWindowHeight() / 2 - 160, 250, 370, grey);

	size_t labelIndex = uiManager->addLabel((int)this->gameEngine->getGameWindowWidth() / 2, (int)this->gameEngine->getGameWindowHeight() / 2 - 130, "Settings", textColor, FONTS::NORMAL);
	this->settingLabels.push_back(labelIndex);

	size_t labelIndex2 = uiManager->addLabel((int)this->gameEngine->getGameWindowWidth() / 2, (int)this->gameEngine->getGameWindowHeight() / 2 - 80, "Master Volume", textColor, FONTS::SMALL);
	this->settingLabels.push_back(labelIndex2);
	size_t masterSliderIndex = uiManager->addSlider({ (int)this->gameEngine->getGameWindowWidth() / 2 - 100, (int)this->gameEngine->getGameWindowHeight() / 2 - 60, 200, 30 }, lightGrey, slider, gameEngine->getMasterVolume());
	this->settingSliders.push_back(masterSliderIndex);

	size_t labelIndex3 = uiManager->addLabel((int)this->gameEngine->getGameWindowWidth() / 2, (int)this->gameEngine->getGameWindowHeight() / 2 - 10, "Music Volume", textColor, FONTS::SMALL);
	this->settingLabels.push_back(labelIndex3);
	size_t musicSliderIndex = uiManager->addSlider({ (int)this->gameEngine->getGameWindowWidth() / 2 - 100, (int)this->gameEngine->getGameWindowHeight() / 2+10, 200, 30 }, lightGrey, slider, gameEngine->getMusicVolume());
	this->settingSliders.push_back(musicSliderIndex);

	size_t labelIndex4 = uiManager->addLabel((int)this->gameEngine->getGameWindowWidth() / 2, (int)this->gameEngine->getGameWindowHeight() / 2 + 60, "Sound Volume", textColor, FONTS::SMALL);
	this->settingLabels.push_back(labelIndex4);
	size_t soundSliderIndex = uiManager->addSlider({ (int)this->gameEngine->getGameWindowWidth() / 2 - 100, (int)this->gameEngine->getGameWindowHeight() / 2+80, 200, 30 }, lightGrey, slider, gameEngine->getSoundVolume());
	this->settingSliders.push_back(soundSliderIndex);

	this->settingButton = uiManager->addButton((int)this->gameEngine->getGameWindowWidth() / 2, (int)this->gameEngine->getGameWindowHeight() / 2 + 160, "Okay", textColor, lightGrey, FONTS::SMALL, { 48,5 }, buttonHover);

	uiManager->getSlider(musicSliderIndex)->onValueChanged(&setMusicVolumeWrapper);
	uiManager->getSlider(masterSliderIndex)->onValueChanged(&setMasterVolumeWrapper);
	uiManager->getSlider(soundSliderIndex)->onValueChanged(&setSoundVolumeWrapper);

	uiManager->getButton(this->settingButton)->onClick(&toggleSettingsWrapper);

	// hide settings ui
	this->toggleSettings();

	// add keybind
	this->inputManager->bindKey(SDLK_ESCAPE, &toggleSettingsWrapper);
}

void Game::nextLevel() {
	Scene* scene = nullptr;
	int idx = std::rand() % 4;

	while (idx == lastSceneIdx) {
		idx = std::rand() % 4;
	}

	if (levelCompletedCounter == 0) {
		switch (idx) {
		case 0:
			scene = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, "../TestTextures/new_bgm.mp3", &initWinterSceneWrapper);
			break;
		case 1:
			scene = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter2.json", 4, "../TestTextures/new_bgm.mp3", &initWinterLakeSceneWrapper);
			break;
		case 2:
			scene = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter3.json", 4, "../TestTextures/new_bgm.mp3", &initWinterRiverSceneWrapper);
			break;
		case 3:
			scene = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter4.json", 4, "../TestTextures/new_bgm.mp3", &initWinterRoadSceneWrapper);
			break;
		default:
			break;
		}
	}
	else {
		switch (idx) {
		case 0:
			scene = new Scene(nullptr, "../TestTextures/winter.json", 4, nullptr, &initWinterSceneWrapper);
			break;
		case 1:
			scene = new Scene(nullptr, "../TestTextures/winter2.json", 4, nullptr, &initWinterLakeSceneWrapper);
			break;
		case 2:
			scene = new Scene(nullptr, "../TestTextures/winter3.json", 4, nullptr, &initWinterRiverSceneWrapper);
			break;
		case 3:
			scene = new Scene(nullptr, "../TestTextures/winter4.json", 4, nullptr, &initWinterRoadSceneWrapper);
			break;
		default:
			break;
		}
	}
	this->lastSceneIdx = idx;

	// load scene
	this->gameEngine->changeScene(scene, false);
}

void Game::init() {
	// seed random algorithm
	std::srand(std::time(0));

	gameEngine = new GameEngine();
	//gameEngine->init(60, "Demo Game", 1920, 1080, 1280, 720);
	gameEngine->init(60, "Demo Game", 1280, 720, 1280, 720);
	this->uiManager = this->gameEngine->getUIManager();
	this->inputManager = this->gameEngine->getInputManager();

	// load fonts
	uiManager->addFont("../TestTextures/Fonts/arial.ttf", 32);
	uiManager->addFont("../TestTextures/Fonts/C&C_RedAlert_LAN.ttf", 64);
	uiManager->addFont("../TestTextures/Fonts/C&C_RedAlert_LAN.ttf", 48);
	uiManager->addFont("../TestTextures/Fonts/arial.ttf", 22);

	// start screen
	Scene* start = new Scene(nullptr, nullptr, 0, "../TestTextures/new_bgm.mp3", &initStartSceneWrapper);
	this->gameEngine->changeScene(start, false);
}

void Game::start() {
	gameEngine->run();
}

int main(int argc, char* argv[]) {
	game = new Game();
	game->init();
	game->start();
	return 0;
}
