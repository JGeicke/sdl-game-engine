#pragma once
#include "SDL.h"
#include <iostream>
/**
 * @brief Structure to represent 2D position and vectors.
*/
struct Vector2 {
	/**
	 * @brief X-component of the vector.
	*/
	int x;
	/**
	 * @brief Y-component of the vector.
	*/
	int y;
};

/**
 * @brief User Input Manager.
*/
class InputManager {
public:
	/**
	 * @brief Update loop of the input manager to handle user input.
	*/
	void update();

	/**
	 * @brief If the game window was closed by the user. Used in the main game loop.
	*/
	bool interrupted;

	/**
	 * @brief Returns x component of current direction based on user input.
	 * @return current x component of direction.
	*/
	int getCurrentDirectionX();

	/**
	 * @brief Returns y component of current direction based on user input.
	 * @return current y component of direction.
	*/
	int getCurrentDirectionY();
private:
	/**
	 * @brief Current direction based on keydown events. Base direction is (0,0).
	*/
	Vector2 direction;

	/**
	 * @brief Checks for user input events.
	*/
	void checkForEvent();

	/**
	 * @brief Current user input event.
	*/
	SDL_Event inputEvent;
};