#pragma once
#include "SDL.h"
#include <iostream>
struct Vector2 {
	int x;
	int y;
};

class InputManager {
public:
	void update();
	bool interrupted;
private:
	Vector2 direction;
	void checkForEvent();
	SDL_Event inputEvent;
};