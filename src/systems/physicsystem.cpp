#include "physicsystem.h"

PhysicSystem::PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager, ComponentManager<Position>* positionManager) {
	this->inputManager = inputManager;
	this->movementManager = movementManager;
	this->positionManager = positionManager;
}
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