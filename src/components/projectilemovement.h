#pragma once
#include "basecomponent.h"
#include "../inputmanager.h"
struct ProjectileMovement : BaseComponent {
public:
	void print() {
		//TODO: projectile movement print
	}

	void init(double angle, unsigned int speed){
		this->angle = angle;
		this->projectileSpeed = speed;
	}

	unsigned int getProjectileSpeed() {
		return projectileSpeed;
	}

	double getAngle() {
		return angle;
	}
private:
	unsigned int projectileSpeed = 0;
	double angle = 0.0;
};