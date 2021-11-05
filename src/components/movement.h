#pragma once
#include "basecomponent.h"
/**
 * @brief Component to hold the attributes involved in movement.
*/
struct Movement : BaseComponent {
public:
	/**
	 * @brief Prints the movement attributes of the component.
	*/
	void print() {
		std::cout << "Movement (Entity: " << entity.uid << ") movement speed: " << movementSpeed << std::endl;
	}

	/**
	 * @brief Sets the movement speed of the component.
	 * @param movespeed - New movement speed.
	*/
	void setMovementSpeed(unsigned int movespeed) {
		movementSpeed = movespeed;
	}

	/**
	 * @brief Gets the movement speed of the component.
	 * @return Movement speed of the component.
	*/
	unsigned int getMovementSpeed() {
		return movementSpeed;
	}
private:
	/**
	 * @brief Movement speed of the entity. Determines how fast the entity can move ingame.
	*/
	unsigned int movementSpeed;
};