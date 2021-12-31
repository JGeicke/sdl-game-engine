#pragma once
#include "SDL.h"
#include <iostream>
#include "util/vector2.h"

/**
 * @brief User Input Manager.
*/
class InputManager {
	// action handler
	typedef void (*actionHandler)();
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
	 * @brief Gets the direction.
	 * @return Current direction.
	*/
	Vector2* getDirection() {
		return &direction;
	}

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

	/**
	 * @brief Returns normalized y component of direction.
	 * @return normalized y component of direction.
	*/
	double getNormalizedDirectionY();

	/**
	 * @brief Returns normalized x component of direction.
	 * @return normalized x component of direction.
	*/
	double getNormalizedDirectionX();

	/**
	 * @brief Returns magnitude of direction vector.
	 * @return Magnitude of direction vector.
	*/
	double getDirectionMagnitude();

	/**
	 * @brief Gets current mouse button input.
	 * @return Current mouse button input.
	*/
	int getMouseButton() {
		return mouseButton;
	}

	/**
	 * @brief Gets current mouse position.
	 * @return Current mouse position.
	*/
	SDL_Point getMousePosition() {
		return mousePosition;
	}

	/**
	 * @brief Adds an action handler function to a key.
	 * @param keyCode - Key code of the key triggering the handler.
	 * @param handler - Handler function
	 * @return Whether the process was successful.
	*/
	bool addActionHandler(int keyCode, actionHandler handler);
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

	/**
	 * @brief Current mouse button input.
	*/
	int mouseButton = -1;

	/**
	 * @brief Current mouse position.
	*/
	SDL_Point mousePosition = { 0,0 };

	/**
	 * @brief Action handler for left mouse button.
	*/
	actionHandler lmbHandler = nullptr;

	/**
	 * @brief Sets the current mouse position.
	*/
	void setCurrentMousePosition();
};