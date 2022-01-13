#include "gameengine.h"
#include "game.h"

Game* game = nullptr;

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

void initWinterEndSceneWrapper() {
	game->initWinterEndScene();
}

void initGameOverSceneWrapper() {
	game->initGameOverScene();
}


void spawnPlayerProjectileWrapper() {
	game->spawnPlayerProjectile();
}

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

		playerHealth->print();
		std::cout << "works great" << std::endl;
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
		Scene* end = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter_lake.json", 4, nullptr, &initWinterEndSceneWrapper);
		this->gameEngine->changeScene(end, false);
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
	Position* playerPosition = gameEngine->getPositionComponent(this->player);
	if (playerPosition != nullptr) {
		Entity e = this->gameEngine->createProjectile("../TestTextures/proj.png", { 6,6 }, 2.0f, { playerPosition->x(), playerPosition->y() }, this->inputManager->getMousePosition(), 5.0f, true);
		Collider* col = this->gameEngine->getColliderComponent(e);
		col->onTriggerEnter(&playerProjectileWrapper);
	}
}

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

	gameEngine->addEnemyMovementComponent(wolf, 1.5, player);
	//gameEngine->setEnemyDestination(wolf, gameEngine->getPositionComponent(player));

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

	gameEngine->addEnemyMovementComponent(wizard, 4.0f);

	Health* healthComponent = gameEngine->addHealthComponent(wizard, health);
	healthComponent->onZeroHealth(&onWizardDeathWrapper);

	this->enemyCount++;

	this->boss = wizard;
}

void Game::initWinterEndScene() {
	this->gameEngine->getPositionComponent(this->player)->setPosition(32 * 26 + 16, 32 * 26 + 16);

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
	initGameplayUI(this->uiManager);
	this->inputManager->addActionHandler(SDL_BUTTON_LEFT, &spawnPlayerProjectileWrapper);

	//player
	this->player = gameEngine->addPlayer("player", true, { 492,1350 }, 5);
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
	playerHealth->print();
	UIManager* uimanager = this->gameEngine->getUIManager();
	uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());


	// TODO: fix player collision with enemies (knockback etc.)
	//wolf
	this->addEnemyWolf({ 1040, 850 }, 50);

	//wolf2
	this->addEnemyWolf({ 840,850 }, 50);

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

void Game::startGame(){
	this->enemyCount = 0;
	// clear start ui
	this->uiManager->clearUI();

	Scene* first = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, nullptr, &initWinterSceneWrapper);
	this->gameEngine->changeScene(first, false);
}

void Game::restartGame() {
	this->enemyCount = 0;
	// clear start ui
	this->uiManager->clearUI();

	Scene* first = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, "../TestTextures/new_bgm.mp3", &initWinterSceneWrapper);
	this->gameEngine->changeScene(first, false);
}

void Game::gameOver() {
	// clear start ui
	this->uiManager->clearUI();

	// start screen
	Scene* gameOver = new Scene("../TestTextures/game_over_tileset.png", "../TestTextures/game_over.json", 1, "../TestTextures/game_over.mp3", &initGameOverSceneWrapper);
	this->gameEngine->changeScene(gameOver, true);
}

void Game::wonGame() {
	// clear start ui
	this->uiManager->clearUI();

	// start screen
	Scene* won = new Scene("../TestTextures/game_over_tileset.png", "../TestTextures/game_over.json", 1, "../TestTextures/win.mp3", &initWinningSceneWrapper);
	this->gameEngine->changeScene(won, true);
}

void Game::quitGame(){
	this->gameEngine->quit();
}

void Game::initStartScene() {
	size_t fontIndex = uiManager->addFont("../TestTextures/Fonts/arial.ttf", 32);
	unsigned int gameWindowWidth = this->gameEngine->getGameWindowWidth();
	unsigned int gameWindowHeight = this->gameEngine->getGameWindowHeight();
	SDL_Color white = { 255,255,255 };
	SDL_Color grey = { 48,48,48 };
	SDL_Color buttonHover = { 77,77,77 };
	Entity bg = gameEngine->addEntity("", false, { (int)(gameWindowWidth/2), (int)(gameWindowHeight/2) });
	gameEngine->addSpriteComponent(bg, "../TestTextures/BG.png", { 1800,893 }, 1.0f);

	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2)-180, "Test Game Title", white, fontIndex);
	Button* startButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Start Game", white, grey, 0, { 10,5 }, buttonHover));
	startButton->onClick(&startGameWrapper);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2)+65, "Quit", white, grey, 0, { 63,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initGameOverScene() {
	SDL_Color white = { 255,255,255 };
	SDL_Color grey = { 48,48,48 };
	SDL_Color buttonHover = { 77,77,77 };
	unsigned int gameWindowWidth = this->gameEngine->getGameWindowWidth();
	unsigned int gameWindowHeight = this->gameEngine->getGameWindowHeight();
	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2) - 180, "Game Over", white, 0);
	Button* startButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Try Again", white, grey, 0, { 10,5 }, buttonHover));
	startButton->onClick(&restartGameWrapper);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2) + 65, "Quit", white, grey, 0, { 48,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initWinningScene() {
	SDL_Color white = { 255,255,255 };
	SDL_Color grey = { 48,48,48 };
	SDL_Color buttonHover = { 77,77,77 };
	unsigned int gameWindowWidth = this->gameEngine->getGameWindowWidth();
	unsigned int gameWindowHeight = this->gameEngine->getGameWindowHeight();
	uiManager->addLabel((gameWindowWidth / 2), (gameWindowHeight / 2) - 180, "You won!", white, 0);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2), (gameWindowHeight / 2), "Quit", white, grey, 0, { 48,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initGameplayUI(UIManager* uiManager) {
	// UI
	SDL_Color grey = { 48,48,48 };
	SDL_Color textColor = { 255,255,255 };
	SDL_Color buttonHover = { 255,192,203 };
	size_t fontIndex = 0;
	size_t progIndex = uiManager->addProgressBar(15, 65, 250, 20, grey, { 44, 135, 26 });
	uiManager->getProgressBar(progIndex)->setProgress(0.4f);

	this->hpBarIndex = progIndex;
}

void Game::init() {
	gameEngine = new GameEngine();
	gameEngine->init(60, "Demo Game", 1280, 720);
	//gameEngine->init(60, "Projects of Bach'e Lor", 1920, 1080);
	this->uiManager = this->gameEngine->getUIManager();
	this->inputManager = this->gameEngine->getInputManager();

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
