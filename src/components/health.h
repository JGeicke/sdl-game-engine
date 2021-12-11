#pragma once
#include "basecomponent.h"
#include <iostream>
/**
 * @brief Health component.
*/
struct Health : BaseComponent {
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
private:
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
	}
};