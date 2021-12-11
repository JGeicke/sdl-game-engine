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

void testWrapper() {
	game->buttonHandler();
}

void Game::buttonHandler() {
	ComponentManager<Health>* manager = this->gameEngine->getHealthManager();
	UIManager* uimanager = this->gameEngine->getUIManager();
	Health* playerHealth = manager->getComponent(this->player);
	playerHealth->takeDamage(25);

	//update ui
	uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());

	playerHealth->print();
}

void Game::initUI(UIManager* uiManager) {
	std::cout << "Test" << std::endl;
	// UI
	SDL_Color grey = { 48,48,48 };
	SDL_Color textColor = { 255,255,255 };
	SDL_Color buttonHover = { 255,192,203 };
	size_t fontIndex = uiManager->addFont("../TestTextures/Fonts/arial.ttf", 32);
	if (fontIndex == SIZE_MAX) return;
	size_t labelIndex = uiManager->addLabel(25, 25, "Testlabel", textColor, fontIndex);
	uiManager->addPanel(10, 20, 300, 50, grey);
	size_t progIndex = uiManager->addProgressBar(15, 65, 250, 20, grey, { 44, 135, 26 });
	uiManager->getProgressBar(progIndex)->setProgress(0.4f);

	this->hpBarIndex = progIndex;
	size_t buttonIndex = uiManager->addButton(500, 20, "Testbutton", textColor, grey, fontIndex, { 10,5 },buttonHover);
	uiManager->getButton(buttonIndex)->onClick(&testWrapper);
}

void Game::init() {
	gameEngine = new GameEngine();
	gameEngine->init(60, "Projects of Bach'e Lor", 1280, 720);
	initUI(gameEngine->getUIManager());

	//player
	this->player = gameEngine->addPlayer({ 840,550 }, 5);
	gameEngine->addSpriteComponent(player, "../TestTextures/char_idle_side.png", { 64, 64 }, 1.5f);
	gameEngine->setCameraFollowTarget(player);

	gameEngine->addAnimatorComponent(player);
	gameEngine->addAnimation(player, STATES::IDLE_SIDE, 5, 160, "../TestTextures/char_idle_side.png");
	gameEngine->addAnimation(player, STATES::WALK_SIDE, 6, 100, "../TestTextures/char_walk_side.png");
	gameEngine->addAnimation(player, STATES::IDLE_UP, 5, 160, "../TestTextures/char_idle_up.png");
	gameEngine->addAnimation(player, STATES::WALK_UP, 6, 100, "../TestTextures/char_walk_up.png");
	gameEngine->addAnimation(player, STATES::IDLE_DOWN, 5, 160, "../TestTextures/char_idle_down.png");
	gameEngine->addAnimation(player, STATES::WALK_DOWN, 6, 100, "../TestTextures/char_walk_down.png");

	Collider* playerCollider = gameEngine->addColliderComponent(player, { 0, 0 }, { 15, 32 }, false);
	Health* playerHealth = gameEngine->addHealthComponent(player, 100);
	playerHealth->print();
	UIManager* uimanager = this->gameEngine->getUIManager();
	uimanager->getProgressBar(hpBarIndex)->setProgress((float)playerHealth->getCurrentHealth() / (float)playerHealth->getMaxHealth());
	playerCollider->onCollisionEnter(&testWrapper);

	//wizard
	Entity wizard = gameEngine->addEntity({ 1040, 850 });
	gameEngine->addSpriteComponent(wizard, "../TestTextures/wizard_idle.png", { 64, 64 }, 1.0f);
	gameEngine->addColliderComponent(wizard, { 0, 0 }, { 30, 53 }, false);
	gameEngine->addAnimatorComponent(wizard);
	gameEngine->addAnimation(wizard, STATES::IDLE_SIDE, 10, 150);

	// scene
	gameEngine->setTilemap("../TestTextures/test_level_1.png", "../TestTextures/level_1_col.json", 3);
	gameEngine->setBGM("../TestTextures/new_bgm.mp3");
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
