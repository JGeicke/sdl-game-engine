/*
#include "SDL.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "components/components.h"
#include "systems/rendersystem.h"
#include "systems/physicsystem.h"
#include "systems/audiosystem.h"
#include "inputmanager.h"
#include "uimanager.h"
*/
#include "gameengine.h"
#include "game.h"

Game* game = nullptr;

void enemyProjectileWrapper(Collider* a, Collider* b) {
	game->enemyProjectileHandler(a, b);
}

void enemyCollisionWrapper(Collider* a, Collider* b) {
	game->enemyCollisionHandler(a,b);
}

void onPlayerDeathWrapper(Health* healthComponent) {
	game->onPlayerDeath(healthComponent);
}

void initStartSceneWrapper() {
	game->initStartScene();
}

void quitGameWrapper() {
	game->quitGame();
}

void startGameWrapper() {
	game->startGame();
}

void initWinterSceneWrapper() {
	game->initWinterScene();
}


void spawnPlayerProjectileWrapper() {
	game->spawnPlayerProjectile();
}



void Game::enemyCollisionHandler(Collider* a, Collider* b) {
	if (b->getEntity().tag == "player") {
		/*
		std::cout << b->getEntity().tag << std::endl;
		ComponentManager<Health>* manager = this->gameEngine->getHealthManager();
		UIManager* uimanager = this->gameEngine->getUIManager();
		Health* playerHealth = manager->getComponent(this->player);
		playerHealth->takeDamage(25);

		//update ui
		uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());

		playerHealth->print();
		*/
		//this->gameEngine->changeScene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, "../TestTextures/bgm_old.mp3");
		//std::cout << "test" << std::endl;
	}

}

void Game::enemyProjectileHandler(Collider* a, Collider* b) {
	if (b->getEntity().tag == "player") {
		ComponentManager<Health>* manager = this->gameEngine->getHealthManager();
		UIManager* uimanager = this->gameEngine->getUIManager();
		Health* playerHealth = manager->getComponent(this->player);
		playerHealth->takeDamage(25);

		//update ui
		uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());

		// delete projectile
		Entity e = a->getEntity();
		this->gameEngine->destroyEntity(e);
		b->resetLastCollision();
	}
}

void Game::onPlayerDeath(Health* healthComponent) {
	std::cout << "Game over" << std::endl;
}

void Game::spawnPlayerProjectile() {
	Position* playerPosition = gameEngine->getPositionComponent(this->player);

	Entity e = this->gameEngine->createProjectile("../TestTextures/proj.png", { 6,6 }, 2.0f, { playerPosition->x(), playerPosition->y() }, this->inputManager->getMousePosition(), 3.0f, true);
	Collider* col = this->gameEngine->getColliderComponent(e);
	col->onTriggerEnter(&enemyCollisionWrapper);
	/* projectile test
	Entity proj = gameEngine->addEntity("projectile", false, { playerPosition->x(), playerPosition->y() });
	gameEngine->addSpriteComponent(proj, "../TestTextures/proj.png", { 6,6 }, 2.0f);
	Collider* projCollider = gameEngine->addColliderComponent(proj, { 0,0 }, { 12,12 }, true);
	//projCollider->onTriggerEnter(&enemyProjectileWrapper);
	gameEngine->addProjectileMovement(proj, { playerPosition->x(), playerPosition->y() }, this->inputManager->getMousePosition(), 3, true);
	*/
}


void Game::initWinterScene() {
	initGameplayUI(this->uiManager);
	this->inputManager->addActionHandler(SDL_BUTTON_LEFT, &spawnPlayerProjectileWrapper);

	//player
	this->player = gameEngine->addPlayer("player", true, { 440,550 }, 5);
	gameEngine->addSpriteComponent(player, "../TestTextures/char_idle_side.png", { 64, 64 }, 1.5f);
	gameEngine->setCameraFollowTarget(player);

	Animator* playerAnimator = gameEngine->addAnimatorComponent(player);
	gameEngine->addAnimation(player, STATES::IDLE_SIDE, 5, 160, "../TestTextures/char_idle_side.png");
	gameEngine->addAnimation(player, STATES::WALK_SIDE, 6, 100, "../TestTextures/char_walk_side.png");
	gameEngine->addAnimation(player, STATES::IDLE_UP, 5, 160, "../TestTextures/char_idle_up.png");
	gameEngine->addAnimation(player, STATES::WALK_UP, 6, 100, "../TestTextures/char_walk_up.png");
	gameEngine->addAnimation(player, STATES::IDLE_DOWN, 5, 160, "../TestTextures/char_idle_down.png");
	gameEngine->addAnimation(player, STATES::WALK_DOWN, 6, 100, "../TestTextures/char_walk_down.png");
	gameEngine->addAnimation(player, STATES::ATK_SIDE, 3, 200, "../TestTextures/char_atk_side.png");
	gameEngine->addAnimation(player, STATES::ATK_DOWN, 3, 200, "../TestTextures/char_atk_down.png");
	gameEngine->addAnimation(player, STATES::ATK_UP, 3, 200, "../TestTextures/char_atk_up.png");

	playerAnimator->markAnimationInterruptible(STATES::ATK_SIDE);
	playerAnimator->markAnimationInterruptible(STATES::ATK_DOWN);
	playerAnimator->markAnimationInterruptible(STATES::ATK_UP);

	Collider* playerCollider = gameEngine->addColliderComponent(player, { 0, 0 }, { 15, 46 }, false);
	Health* playerHealth = gameEngine->addHealthComponent(player, 100);
	playerHealth->onZeroHealth(&onPlayerDeathWrapper);
	playerHealth->print();
	UIManager* uimanager = this->gameEngine->getUIManager();
	uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());

	//wizard
	Entity wizard = gameEngine->addEntity("enemy", false,{ 1040, 850 });
	gameEngine->addSpriteComponent(wizard, "../TestTextures/wizard_idle.png", { 64, 64 }, 1.0f);
	Collider* wizardCollider = gameEngine->addColliderComponent(wizard, { 0, 0 }, { 30, 53 }, false);
	wizardCollider->onCollisionEnter(&enemyCollisionWrapper);
	gameEngine->addAnimatorComponent(wizard);
	gameEngine->addAnimation(wizard, STATES::IDLE_SIDE, 10, 150);
	
	gameEngine->addEnemyMovementComponent(wizard, 1.5);
	gameEngine->setEnemyDestination(wizard, gameEngine->getPositionComponent(player));

	/* projectile test
	ComponentManager<ProjectileMovement>* man = gameEngine->getProjectileMovementManager();
	Entity proj = gameEngine->addEntity("projectile", false, { 1040, 850 });
	gameEngine->addSpriteComponent(proj, "../TestTextures/proj.png", {6,6}, 2.0f);
	Collider* projCollider = gameEngine->addColliderComponent(proj, { 0,0 }, { 12,12 }, true);
	projCollider->onTriggerEnter(&enemyProjectileWrapper);
	gameEngine->addProjectileMovement(proj, { 1040, 850 }, {840, 550}, 3);
	*/
}

void Game::startGame(){
	// clear start ui
	this->uiManager->clearUI();

	Scene* first = new Scene("../TestTextures/winter_tileset.png", "../TestTextures/winter.json", 4, nullptr, &initWinterSceneWrapper);
	this->gameEngine->loadScene(first);
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
	uiManager->addLabel((gameWindowWidth / 2)-110, (gameWindowHeight / 2)-180, "Test Game Title", white, fontIndex);
	Button* startButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2)-80, (gameWindowHeight / 2), "Start Game", white, grey, 0, { 10,5 }, buttonHover));
	startButton->onClick(&startGameWrapper);
	Button* quitButton = uiManager->getButton(uiManager->addButton((gameWindowWidth / 2) - 27, (gameWindowHeight / 2)+65, "Quit", white, grey, 0, { 63,5 }, buttonHover));
	quitButton->onClick(&quitGameWrapper);
}

void Game::initGameplayUI(UIManager* uiManager) {
	std::cout << "Test" << std::endl;
	// UI
	SDL_Color grey = { 48,48,48 };
	SDL_Color textColor = { 255,255,255 };
	SDL_Color buttonHover = { 255,192,203 };
	//size_t fontIndex = uiManager->addFont("../TestTextures/Fonts/arial.ttf", 32);
	size_t fontIndex = 0;
	size_t labelIndex = uiManager->addLabel(25, 25, "Testlabel", textColor, fontIndex);
	uiManager->addPanel(10, 20, 300, 50, grey);
	size_t progIndex = uiManager->addProgressBar(15, 65, 250, 20, grey, { 44, 135, 26 });
	uiManager->getProgressBar(progIndex)->setProgress(0.4f);

	this->hpBarIndex = progIndex;
	size_t buttonIndex = uiManager->addButton(500, 20, "Testbutton", textColor, grey, fontIndex, { 10,5 },buttonHover);
	//uiManager->getButton(buttonIndex)->onClick(&testWrapper);
}

void Game::init() {
	gameEngine = new GameEngine();
	gameEngine->init(60, "Projects of Bach'e Lor", 1280, 720);
	this->uiManager = this->gameEngine->getUIManager();
	this->inputManager = this->gameEngine->getInputManager();

	// start screen
	Scene* start = new Scene(nullptr, nullptr, 0, "../TestTextures/new_bgm.mp3", &initStartSceneWrapper);
	this->gameEngine->loadScene(start);
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
