#pragma once
#include "SDL.h"
#include <string>
/**
 * @brief Class representing the game window.
*/
class Window {
public:
	/**
	 * @brief Constructor of a window object.
	 * @param title - Title of the game window.
	 * @param width - Width of the game window.
	 * @param height - Height of the game window.
	*/
	Window(std::string title, int width, int height) {
		this->windowTitle = title;
		this->width = width;
		this->height = height;
	}

	/**
	 * @brief Initializes the game window.
	 * @return Whether the game window was successfully initialized.
	*/
	bool initWindow();

	/**
	* @brief Window destructor. Destroys the SDL_Renderer and the SDL_Window. 
	*/
	~Window() {
		if (window) {
			SDL_DestroyWindow(window);
		}
		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
	}

	/**
	 * @brief Gets the height of the game window.
	 * @return Height of the game window.
	*/
	unsigned int getWindowHeight() {
		return height;
	}

	/**
	 * @brief Gets the width of the game window.
	 * @return Width of the game window.
	*/
	unsigned int getWindowWidth() {
		return width;
	}

	/**
	 * @brief Gets the SDL_Window object of the window.
	 * @return Pointer to the SDL_Window object.
	*/
	SDL_Window* getWindow() {
		return window;
	}

	/**
	 * @brief Gets the SDL_Renderer object of the window
	 * @return Pointer to the SDL_Renderer object.
	*/
	SDL_Renderer* getRenderer() {
		return renderer;
	}
private:
	/**
	 * @brief Width of the game window.
	*/
	unsigned int width = 1280;
	/**
	 * @brief Height of the game window.
	*/
	unsigned int height = 720;

	/**
	 * @brief Title of the game window.
	*/
	std::string windowTitle = "Placeholder";

	/**
	 * @brief Pointer to the SDL_Window.
	*/
	SDL_Window* window = nullptr;
	/**
	 * @brief Pointer to the SDL_Renderer.
	*/
	SDL_Renderer* renderer = nullptr;
};