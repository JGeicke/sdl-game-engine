#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include "../entity.h"
/**
 * @brief Abstract base struct for components.
*/
struct BaseComponent {

	/**
	 * @brief Printing the component.
	*/
	virtual void print() = 0;

	void setEntity(Entity e) {
		this->entity = e;
	}

	Entity getEntity() {
		return entity;
	}
private:
	Entity entity;
};
#endif // !BASECOMPONENT_H
