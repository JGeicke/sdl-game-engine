#pragma once
#include "basecomponent.h"
#include "../inputmanager.h"
#include <iostream>
/**
 * @brief Component to hold the attributes involved in projectile movement.
*/
struct ProjectileMovement : BaseComponent {
public:
	/**
	 * @brief Prints the projectile movement component.
	*/
	void print() { 
		std::cout << "Projectile Movement (Entity: " << entity.uid << ") Angle: " << angle << " | Projectile speed: " << projectileSpeed << std::endl;
	}

	/**
	 * @brief Initializes the projectile movement component.
	 * @param angle - Angle between start point and target point.
	 * @param speed - Projectile speed.
	*/
	void init(double angle, float speed){
		this->angle = angle;
		this->projectileSpeed = speed;
	}

	/**
	 * @brief Gets the projectile speed.
	 * @return Projectile speed.
	*/
	float getProjectileSpeed() {
		return projectileSpeed;
	}

	/**
	 * @brief Gets the movement angle.
	 * @return Movement angle of the projectile.
	*/
	double getAngle() {
		return angle;
	}
private:
	/**
	 * @brief The projectile speed.
	*/
	float projectileSpeed = 0;
	/**
	 * @brief Movement angle of the projectile.
	*/
	double angle = 0.0;
};