#include "inputmanager.h"
/**
* @brief Update loop of the input manager to handle user input.
*/
void InputManager::update() {
	checkForEvent();
	std::cout << "current direction: (" << direction.x << " | " << direction.y << ");\n" << std::endl;
}

/**
* @brief Checks for user input events. Interrupts the game loop if the user closes the game window. Sets the current direction based on the directional input of the user. If a key is released, reset the current direction component back to 0.
*/
void InputManager::checkForEvent() {
	SDL_PollEvent(&inputEvent);
	switch (inputEvent.type)
	{
	case SDL_QUIT:
		interrupted = true;
		break;
	case SDL_KEYDOWN:
		// user directional input
		switch (inputEvent.key.keysym.sym)
		{
		case SDLK_w:
			// up
			direction.y = -1;
			break;
		case SDLK_s:
			// down
			direction.y = 1;
			break;
		case SDLK_a:
			// left
			direction.x = -1;
			break;
		case SDLK_d:
			// right
			direction.x = 1;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		// reset current direction depending on released key
		switch (inputEvent.key.keysym.sym)
		{
		case SDLK_w:
			// up
			direction.y = 0;
			break;
		case SDLK_s:
			// down
			direction.y = 0;
			break;
		case SDLK_a:
			// left
			direction.x = 0;
			break;
		case SDLK_d:
			// right
			direction.x = 0;
			break;
		default:
			break;
		}
	default:
		break;
	}
}