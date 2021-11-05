#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
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
protected:
	/**
	 * @brief Entity that owns the component.
	*/
	Entity entity;
};
#endif // !BASECOMPONENT_H
