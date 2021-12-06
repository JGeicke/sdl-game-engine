#pragma once
#include "SDL.h"
#include <string>
class Window {
public:
	Window(std::string title, int width, int height) {
		this->windowTitle = title;
		this->width = width;
		this->height = height;
	}

	bool initWindow();

	~Window() {
		if (window) {
			SDL_DestroyWindow(window);
		}
		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
	}

	unsigned int getWindowHeight() {
		return height;
	}

	unsigned int getWindowWidth() {
		return width;
	}

	SDL_Window* getWindow() {
		return window;
	}

	SDL_Renderer* getRenderer() {
		return renderer;
	}
private:
	unsigned int width = 1280;
	unsigned int height = 720;

	std::string windowTitle = "Placeholder";

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};