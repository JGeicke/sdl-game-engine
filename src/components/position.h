#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include "basecomponent.h"
/**
 * @brief Component to represent the position (x-/y-position) of the entity in the game.
*/
struct Position: BaseComponent {
	/**
	 * @brief X-position of entity in the game.
	*/
	int x = 0;

	/**
	 * @brief Y-position of entity in the game.
	*/
	int y = 0;

	/**
	 * @brief Prints the x & y position of the component.
	*/
	void print() {
		std::cout << "Position (Entity: " << entity.uid << ") X: " << x  << " | Y: " << y << std::endl;
	}
};
#endif // !POSITION_H

