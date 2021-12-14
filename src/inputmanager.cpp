#include "inputmanager.h"
/**
* @brief Update loop of the input manager to handle user input.
*/
void InputManager::update() {
	mouseButton = -1;
	checkForEvent();
	//std::cout << "current direction: (" << direction.x << " | " << direction.y << ");\n" << std::endl;
}

/**
* @brief Checks for user input events. Interrupts the game loop if the user closes the game window. Sets the current direction based on the directional input of the user. If a key is released, reset the current direction component back to 0.
*/
void InputManager::checkForEvent() {
	// check for events
	while (SDL_PollEvent(&inputEvent)) {
		switch (inputEvent.type)
		{
		case SDL_QUIT:
			interrupted = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			// mouse click
			mouseButton = inputEvent.button.button;
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
				if (direction.y == -1) {
					direction.y = 0;
				}
				break;
			case SDLK_s:
				// down
				if (direction.y == 1) {
					direction.y = 0;
				}
				break;
			case SDLK_a:
				// left
				if (direction.x == -1) {
					direction.x = 0;
				}
				break;
			case SDLK_d:
				// right
				if (direction.x == 1) {
					direction.x = 0;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

/**
* @brief Returns x component of current direction based on user input.
* @return current x component of direction.
*/
int InputManager::getCurrentDirectionX() {
	return direction.x;
}

/**
* @brief Returns y component of current direction based on user input.
* @return current y component of direction.
*/
int InputManager::getCurrentDirectionY() {
	return direction.y;
}

/**
* @brief Returns normalized y component of direction.
* @return normalized y component of direction.
*/
double InputManager::getNormalizedDirectionY() {
	//std::cout << "normalized y: " << (direction.y / direction.getMagnitude()) << std::endl;
	return direction.y / direction.getMagnitude();
}

/**
* @brief Returns normalized x component of direction.
* @return normalized x component of direction.
*/
double InputManager::getNormalizedDirectionX() {
	//std::cout << "normalized x: " << (direction.x / direction.getMagnitude()) << std::endl;
	return direction.x / direction.getMagnitude();
}

/**
* @brief Returns magnitude of direction vector.
* @return Magnitude of direction vector.
*/
double InputManager::getDirectionMagnitude() {
	return direction.getMagnitude();
}