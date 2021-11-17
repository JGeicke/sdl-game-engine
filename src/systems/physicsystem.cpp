#include "physicsystem.h"

/**
* @brief Constructor of physic system to set needed references.
* @param inputManager - Input manager to handle user inputs.
* @param movementManager - Movement Manager to gain access to movement components.
* @param positionManager - Position manager to gain access to position components.
*/
PhysicSystem::PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager,
	ComponentManager<Position>* positionManager, ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager) {
	this->inputManager = inputManager;
	this->movementManager = movementManager;
	this->positionManager = positionManager;
	this->spriteManager = spriteManager;
	this->animatorManager = animatorManager;
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
		Sprite* spriteComponent = spriteManager->getComponent(movementComponent->getEntity());
		Animator* animatorComponent = animatorManager->getComponent(movementComponent->getEntity());
		
		if (inputManager->getDirectionMagnitude() > 0.0) {
			// moving
			positionComponent->x += inputManager->getNormalizedDirectionX() * movementComponent->getMovementSpeed();
			positionComponent->y += inputManager->getNormalizedDirectionY() * movementComponent->getMovementSpeed();

			// adjust animator
			animatorComponent->setState(STATES::WALK);

			// flip sprite depending on user input
			if (inputManager->getCurrentDirectionX() > 0) {
				spriteComponent->setTextureFlip(SDL_FLIP_HORIZONTAL);
				animatorComponent->setDirection(DIRECTION::SIDE);
			}
			else if (inputManager->getCurrentDirectionX() < 0) {
				spriteComponent->setTextureFlip(SDL_FLIP_NONE);
				animatorComponent->setDirection(DIRECTION::SIDE);
			}
			else {
				(inputManager->getCurrentDirectionY() > 0) ? animatorComponent->setDirection(DIRECTION::DOWN) : animatorComponent->setDirection(DIRECTION::UP);
			}
		}
		else {
			// idling
			animatorComponent->setState(STATES::IDLE);
		}
	}
}