#pragma once
#include "../entity.h"
/**
 * @brief Abstract base struct for components.
*/
struct BaseComponent {

	/**
	 * @brief Prints the component.
	*/
	virtual void print() = 0;

	/**
	 * @brief Sets the reference to the entity that owns the component. This is needed to avoid multiple iterations when more than 1 component is used by a game system.
	 * @param e - Entity that owns the component.
	*/
	void setEntity(Entity e) {
		this->entity = e;
	}

	/**
	 * @brief Return owner entity.
	 * @return - Entity that owns the component
	*/
	Entity getEntity() {
		return entity;
	}

	/**
	 * @brief Activates or deactivates the component.
	 * @param isActive - Whether the component is active or not
	*/
	void setActive(bool isActive) {
		active = isActive;
	}

	/**
	 * @brief Checks if the component is active.
	 * @return Whether the component is active.
	*/
	bool isActive() {
		return active;
	}
protected:
	/**
	 * @brief Entity that owns the component.
	*/
	Entity entity;

	/**
	 * @brief Whether the component is active.
	*/
	bool active = true;


};