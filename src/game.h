#pragma once
#include "gameengine.h"
class Game {
public:
	void init();
	void start();

	void buttonHandler();
private:
	void initUI(UIManager* uiManager);

	GameEngine* gameEngine;
	UIManager* uiManager;

	Entity player;
};