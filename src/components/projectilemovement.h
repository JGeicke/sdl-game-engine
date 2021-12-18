#pragma once
#include "basecomponent.h"
#include "../inputmanager.h"
struct ProjectileMovement : BaseComponent {
public:
	void print() {
		//TODO: projectile movement print
	}

	void init(Vector2 direction, unsigned int speed){
		this->direction = direction;
		this->projectileSpeed = speed;
	}

	unsigned int getProjectileSpeed() {
		return projectileSpeed;
	}

	double getDirectionMagnitude() {
		return direction.getMagnitude();
	}

	double getNormalizedDirectionY() {
		return direction.getNormalizedY();
	}

	double getNormalizedDirectionX() {
		return direction.getNormalizedX();
	}
private:
	unsigned int projectileSpeed = 0;
	Vector2 direction = { 0,0 };
};