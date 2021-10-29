#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

/**
 * @brief Abstract base struct for components.
*/
struct BaseComponent {

	/**
	 * @brief Printing the component.
	*/
	virtual void print() = 0;
};
#endif // !BASECOMPONENT_H
