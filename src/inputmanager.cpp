#include "inputmanager.h"
void InputManager::update() {
	checkForEvent();
	std::cout << "current direction: (" << direction.x << " | " << direction.y << ");\n" << std::endl;
}

void InputManager::checkForEvent() {
	SDL_PollEvent(&inputEvent);
	switch (inputEvent.type)
	{
	case SDL_QUIT:
		// TODO: break gameloop when window is closed
		interrupted = true;
		break;
	case SDL_KEYDOWN:
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