#include "physicsystem.h"
/**
* @brief Constructor of physic system to set needed references.
* @param inputManager - Input manager to handle user inputs.
* @param movementManager - Movement Manager to gain access to movement components.
* @param positionManager - Position manager to gain access to position components.
* @param spriteManager - Sprite manager to access to sprite components.
* @param animatorManager - Animator manager to access animator components.
* @param colliderManager - Collider manager to access collider components for collisions.
*/
PhysicSystem::PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager, ComponentManager<Position>* positionManager,
	ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager, ComponentManager<Collider>* colliderManager) {
	this->inputManager = inputManager;
	this->movementManager = movementManager;
	this->positionManager = positionManager;
	this->spriteManager = spriteManager;
	this->animatorManager = animatorManager;
	this->colliderManager = colliderManager;
}

/**
* @brief Render system update loop. Iterates over every movement component and changes the position component of the same entity. 
*/
void PhysicSystem::update() {
	handlePlayerMovement();
	handleCollision();
}
/**
* @brief Handles the player movement each frame.
*/
void PhysicSystem::handlePlayerMovement() {
	unsigned int componentCount = movementManager->getComponentCount();
	for (size_t i = 0; i < componentCount; i++)
	{
		Movement* movementComponent = movementManager->getComponentWithIndex(i);
		Position* positionComponent = positionManager->getComponent(movementComponent->getEntity());
		Sprite* spriteComponent = spriteManager->getComponent(movementComponent->getEntity());
		Animator* animatorComponent = animatorManager->getComponent(movementComponent->getEntity());

		if (inputManager->getDirectionMagnitude() > 0.0) {
			// moving
			int newX = inputManager->getNormalizedDirectionX() * movementComponent->getMovementSpeed();
			int newY = inputManager->getNormalizedDirectionY() * movementComponent->getMovementSpeed();
			positionComponent->movePosition(newX, newY);

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

/**
* @brief Handles collision between entities.
*/
void PhysicSystem::handleCollision(){
	calculateColliderPositions();
	detectCollisions();
}

/**
 * @brief Calculates the positions of the colliders.
*/
void PhysicSystem::calculateColliderPositions(){
	unsigned int componentCount = colliderManager->getComponentCount();

	for (size_t i = 0; i < componentCount; i++) {
		Collider* currentCollider = colliderManager->getComponentWithIndex(i);

		if (movementManager->hasComponent(currentCollider->getEntity())) {
			// collider on moving player object
			Position* currentPosition = positionManager->getComponent(currentCollider->getEntity());
			adjustColliderPosition(currentCollider, currentPosition);
		}
	}
}

/**
* @brief Adjusts the position of the collider based on the position.
*/
void PhysicSystem::adjustColliderPosition(Collider* collider, Position* position) {
	SDL_Point* colliderOffset = collider->getColliderOffset();
	SDL_Point* colliderSize = collider->getColliderSize();

	int newX = (position->x() - (colliderSize->x / 2)) + colliderOffset->x;
	int newY = (position->y() - (colliderSize->y / 2)) + colliderOffset->y;

	collider->setColliderRect(newX, newY);
}

/**
* @brief Detects collisions between colliders.
*/
void PhysicSystem::detectCollisions() {
	size_t componentCount = movementManager->getComponentCount();
	size_t colliderCount = colliderManager->getComponentCount();

	for (size_t i = 0;i < componentCount; i++) {
		size_t collisionCounter = 0;

		Movement* currentMovement = movementManager->getComponentWithIndex(i);
		Position* currentPosition = positionManager->getComponent(currentMovement->getEntity());
		Collider* currentCollider = colliderManager->getComponent(currentMovement->getEntity());

		if (currentCollider->isActive()) {
			for (size_t z = 0; z < colliderCount; z++)
			{
				Collider* nextCollider = colliderManager->getComponentWithIndex(z);

				if (nextCollider->isActive()) {
					// check if both entities
					if (nextCollider->getEntity().uid != currentMovement->getEntity().uid) {
						if (SDL_HasIntersection(currentCollider->getColliderRect(), nextCollider->getColliderRect()) == SDL_TRUE) {
							// collision
							collisionCounter++;
							// execute collider collision behaviour
							if (nextCollider->isTrigger()) {
								nextCollider->collision(currentCollider->getEntity());
							}
							else if (currentCollider->isTrigger()) {
								currentCollider->collision(nextCollider->getEntity());
							}
							else {
								currentCollider->collision(nextCollider->getEntity());
								nextCollider->collision(currentCollider->getEntity());

								// adjust position
								currentPosition->restoreLastPosition();
								adjustColliderPosition(currentCollider, currentPosition);
							}
						}
					}
				}
			}
		}

		// if current collider does not collide with another collider, reset lastCollision
		if (collisionCounter == 0 && !currentCollider->getLastCollision().uid == 0) {
			Collider* lastCollider = colliderManager->getComponent(currentCollider->getLastCollision());
			if (lastCollider->getLastCollision().uid == currentCollider->getEntity().uid) {
				// check if last collision was with current entity. if this is the case, reset last collision.
				lastCollider->resetLastCollision();
			}
			currentCollider->resetLastCollision();
		}
	}
}