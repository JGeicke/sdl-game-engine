#include "physicsystem.h"

/**
* @brief Constructor of physic system to set needed references.
* @param inputManager - Input manager to handle user inputs.
* @param movementManager - Movement Manager to gain access to movement components.
* @param positionManager - Position manager to gain access to position components.
*/
PhysicSystem::PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager, ComponentManager<Position>* positionManager) {
	this->inputManager = inputManager;
	this->movementManager = movementManager;
	this->positionManager = positionManager;
}

/**
* @brief Render system update loop. Iterates over every movement component and changes the position component of the same entity. 
*/
void PhysicSystem::update() {
	unsigned int componentCount = movementManager->getComponentCount();
	for (size_t i = 0; i < componentCount; i++)
	{
		Movement* movementComponent = movementManager->getComponentWithIndex(i);
		Position* positionComponent = positionManager->getComponent(movementComponent->getEntity());
		
		if (inputManager->getDirectionMagnitude() > 0.0) {
			positionComponent->x += inputManager->getNormalizedDirectionX() * movementComponent->getMovementSpeed();
			positionComponent->y += inputManager->getNormalizedDirectionY() * movementComponent->getMovementSpeed();
		}
	}
}