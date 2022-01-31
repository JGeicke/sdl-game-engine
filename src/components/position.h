#pragma once
#include <iostream>
#include "basecomponent.h"
#include "SDL.h"
/**
 * @brief Component to represent the position (x-/y-position) of the entity in the game.
*/
struct Position: BaseComponent {
public:
	/**
	 * @brief Prints the x & y position of the component.
	*/
	void print() {
		std::cout << "Position (Entity: " << entity.uid << ") X: " << currentX  << " | Y: " << currentY << std::endl;
	}

	/**
	 * @brief Moves position.
	 * @param newX - X position change.
	 * @param newY - Y position change.
	*/
	void movePosition(float newX, float newY) {
		lastX = currentX;
		lastY = currentY;

		currentX += newX;
		currentY += newY;
	}

	/**
	 * @brief Sets the position.
	 * @param newX - New x position.
	 * @param newY - New y position.
	*/
	void setPosition(float newX, float newY) {
		lastX = currentX;
		lastY = currentY;

		currentX = newX;
		currentY = newY;
	}
	/**
	 * @brief Gets x position.
	 * @return X position.
	*/
	int x() {
		return (int)currentX;
	}

	/**
	 * @brief Gets y position.
	 * @return Y position.
	*/
	int y() {
		return (int)currentY;
	}

	/**
	 * @brief Restores last position.
	*/
	void restoreLastPosition() {
		currentX = lastX;
		currentY = lastY;
	}
private:
	/**
	 * @brief Current x position.
	*/
	float currentX = 0.0f;

	/**
	 * @brief Current y position.
	*/
	float currentY = 0.0f;;

	/**
	 * @brief Last x position.
	*/
	float lastX = 0.0f;;

	/**
	 * @brief Last y position.
	*/
	float lastY = 0.0f;;


};

