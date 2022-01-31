#include "window.h"
/**
* @brief Initializes the game window.
* @return Whether the game window was successfully initialized.
*/
bool Window::initWindow() {
	this->window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (this->window == nullptr) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", "Could not initialize window of game engine.", NULL);
		return false;
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == nullptr) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", "Could not initialize renderer of game engine.", NULL);
		return false;
	}
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	return true;
}

/**
* @brief Sets the icon of the window.
* @param filePath - Filepath to icon.
*/
void Window::setWindowIcon(const char* filePath) {
	SDL_Surface* icon = IMG_Load(filePath);
	if (icon != nullptr && window != nullptr) {
		SDL_SetWindowIcon(window, icon);
	}
	else {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization error", "Could not load icon of game window.", NULL);
	}
}