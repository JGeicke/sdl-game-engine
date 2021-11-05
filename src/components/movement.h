#pragma once
#include "basecomponent.h"
struct Movement : BaseComponent {
public:
	void print() {
		//todo
	}

	void setMovementSpeed(unsigned int movespeed) {
		movementSpeed = movespeed;
	}

	unsigned int getMovementSpeed() {
		return movementSpeed;
	}
private:
	unsigned int movementSpeed;
};