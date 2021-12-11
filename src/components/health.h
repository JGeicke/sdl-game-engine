#pragma once
#include "basecomponent.h"
#include <iostream>
/**
 * @brief Health component.
*/
struct Health : BaseComponent {
	// function pointer
	typedef void (*healthHandlerFunction)(Health*);
public:
	/**
	 * @brief Prints the collider component.
	*/
	void print() {
		std::cout << "Health (Entity: " << entity.uid << ") Current Health: " << this->currentHealth<<"/"<<this->maxHealth << std::endl;
	}

	/**
	 * @brief Initializes the health component.
	 * @param maximumHealth - Maximum health value.
	*/
	void init(int maximumHealth) {
		this->maxHealth = this->currentHealth = maximumHealth;
	}

	/**
	 * @brief Reduces the health by the incoming damage.
	 * @param damage - Incoming damage.
	*/
	void takeDamage(unsigned int damage) {
		changeCurrentHealth((int)(damage * -1));
	}

	/**
	 * @brief Restores the health by a certain amount health.
	 * @param healAmount - Amount of health to restore.
	*/
	void restoreHealth(unsigned int healthAmount) {
		changeCurrentHealth((int)healthAmount);
	}

	/**
	 * @brief Gets the current health.
	 * @return Current health.
	*/
	int getCurrentHealth() {
		return currentHealth;
	}

	/**
	 * @brief Gets the maximum health.
	 * @return Maximum health.
	*/
	int getMaxHealth() {
		return maxHealth;
	}

	/**
	 * @brief Sets the maximum health.
	 * @param maxHealth - Maxiumum health value.
	*/
	void setMaxHealth(int maxHealth) {
		this->maxHealth = maxHealth;
		if (this->currentHealth > maxHealth) {
			this->currentHealth = maxHealth;
		}
	}

	/**
	 * @brief Sets the current health.
	 * @param currentHealth - Current health value.
	*/
	void setCurrentHealth(int currentHealth) {
		this->currentHealth = (currentHealth <= maxHealth) ? currentHealth : maxHealth;
	}

	/**
	 * @brief Sets the zero health handler of the component.
	 * @param onZeroHealthHandler - Zero health handler function.
	*/
	void onZeroHealth(healthHandlerFunction onZeroHealthHandler) {
		this->onZeroHealthHandler = onZeroHealthHandler;
		hasZeroHealthHandler = true;
	}

	/**
	 * @brief Sets the full health handler of the component.
	 * @param onFullHealthHandler - Full health handler function.
	*/
	void onMaxHealth(healthHandlerFunction onFullHealthHandler) {
		this->onFullHealthHandler = onFullHealthHandler;
		hasFullHealthHandler = true;
	}
private:

	/**
	 * @brief Handler function when the health reaches zero.
	*/
	healthHandlerFunction onZeroHealthHandler = nullptr;

	/**
	 * @brief Whether the component has a on zero health handler function.
	*/
	bool hasZeroHealthHandler = false;

	/**
	 * @brief Handler function when the health reaches full.
	*/
	healthHandlerFunction onFullHealthHandler = nullptr;

	/**
	 * @brief Whether the component has a on full health handler function.
	*/
	bool hasFullHealthHandler = false;
	/**
	 * @brief Maximum health.
	*/
	int maxHealth;
	/**
	 * @brief Current health value. Cannot excede the maximum health value. If the current health reaches 0 or below, the entity dies.
	*/
	int currentHealth;

	/**
	 * @brief Changes the current health value by a certain amount.
	 * @param value - amount of health to change the current health with.
	*/
	void changeCurrentHealth(int value) {
		if (currentHealth + value < 0) {
			currentHealth = 0;
		}
		else {
			currentHealth = ((currentHealth + value) > maxHealth) ? maxHealth : currentHealth + value;
		}

		// handle full health
		if (hasFullHealthHandler && currentHealth == maxHealth) {
			onFullHealthHandler(this);
		}

		if (hasZeroHealthHandler && currentHealth == 0) {
			onZeroHealthHandler(this);
		}
	}
};