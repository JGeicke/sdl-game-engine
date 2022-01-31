#pragma once
#include "basecomponent.h"
/**
 * @brief Camera follow component. The camera follows the position of the entity which holds an camera follow component.
*/
struct CameraFollow : BaseComponent {
	/**
	 * @brief Prints the camera follow target of the component.
	*/
	void print() {
		std::cout << "Camera Follow (Entity: " << entity.uid << ")" << std::endl;
	}
};