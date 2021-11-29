#ifndef POSITION_H
#define POSITION_H
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
		std::cout << "Position (Entity: " << entity.uid << ") X: " << currentPos.x  << " | Y: " << currentPos.y << std::endl;
	}

	/**
	 * @brief Moves position.
	 * @param newX - X position change.
	 * @param newY - Y position change.
	*/
	void movePosition(int newX, int newY) {
		lastPos.x = currentPos.x;
		lastPos.y = currentPos.y;

		currentPos.x += newX;
		currentPos.y += newY;
	}

	/**
	 * @brief Sets the position.
	 * @param newX - New x position.
	 * @param newY - New y position.
	*/
	void setPosition(int newX, int newY) {
		lastPos.x = currentPos.x;
		lastPos.y = currentPos.y;

		currentPos.x = newX;
		currentPos.y = newY;
	}
	/**
	 * @brief Gets x position.
	 * @return X position.
	*/
	int x() {
		return currentPos.x;
	}

	/**
	 * @brief Gets y position.
	 * @return Y position.
	*/
	int y() {
		return currentPos.y;
	}

	/**
	 * @brief Restores last position.
	*/
	void restoreLastPosition() {
		currentPos.x = lastPos.x;
		currentPos.y = lastPos.y;
	}
private:
	/**
	 * @brief Position.
	*/
	SDL_Point currentPos = { 0,0 };

	/**
	 * @brief Last position.
	*/
	SDL_Point lastPos = { 0,0 };
};
#endif // !POSITION_H

