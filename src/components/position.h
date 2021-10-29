#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include "basecomponent.h"
/**
 * @brief Struct to represent position component that stores the x-/y-position of the entity in the game.
*/
struct Position: BaseComponent {
	/**
	 * @brief X-position of entity in the game.
	*/
	int x;

	/**
	 * @brief Y-position of entity in the game.
	*/
	int y;

	/**
	 * @brief Printing the x & y position of the component.
	*/
	void print() {
		std::cout << "X: " << x  << " | Y: " << y << std::endl;
	}
};
#endif // !POSITION_H

