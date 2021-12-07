#include "physicsystem.h"
/**
* @brief Constructor of physic system to set needed references.
* @param inputManager - Input manager to handle user inputs.
* @param playerMovement - Movement component of player.
* @param positionManager - Position manager to gain access to position components.
* @param spriteManager - Sprite manager to access to sprite components.
* @param animatorManager - Animator manager to access animator components.
* @param colliderManager - Collider manager to access collider components for collisions.
*/
PhysicSystem::PhysicSystem(InputManager* inputManager, Movement* playerMovement, ComponentManager<Position>* positionManager,
	ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager, ComponentManager<Collider>* colliderManager) {
	this->inputManager = inputManager;
	this->playerMovement = playerMovement;
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
	if(playerMovement != nullptr)
	{
		Position* positionComponent = positionManager->getComponent(this->playerMovement->getEntity());
		Sprite* spriteComponent = spriteManager->getComponent(this->playerMovement->getEntity());
		Animator* animatorComponent = animatorManager->getComponent(this->playerMovement->getEntity());

		if (inputManager->getDirectionMagnitude() > 0.0) {
			// moving
			int newX = (int)(inputManager->getNormalizedDirectionX() * this->playerMovement->getMovementSpeed());
			int newY = (int)(inputManager->getNormalizedDirectionY() * this->playerMovement->getMovementSpeed());
			positionComponent->movePosition(newX, newY);

			// check if sprite component and animator are present
			if (animatorComponent != nullptr && spriteComponent != nullptr) {
				// adjust animator
				// flip sprite depending on user input
				if (inputManager->getCurrentDirectionX() > 0) {
					spriteComponent->setTextureFlip(SDL_FLIP_HORIZONTAL);
					animatorComponent->setState(STATES::WALK_SIDE);
				}
				else if (inputManager->getCurrentDirectionX() < 0) {
					spriteComponent->setTextureFlip(SDL_FLIP_NONE);
					animatorComponent->setState(STATES::WALK_SIDE);
				}
				else {
					if (inputManager->getCurrentDirectionY() > 0) {
						animatorComponent->setState(STATES::WALK_DOWN);
					}
					else { 
						animatorComponent->setState(STATES::WALK_UP); 
					}
				}
			}
		}
		else if(animatorComponent != nullptr){
			// idling based on previous animation
			size_t state = animatorComponent->getState();
			switch (state) {
			case STATES::WALK_DOWN:
				animatorComponent->setState(STATES::IDLE_DOWN);
				break;
			case STATES::WALK_UP:
				animatorComponent->setState(STATES::IDLE_UP);
				break;
			case STATES::WALK_SIDE:
				animatorComponent->setState(STATES::IDLE_SIDE);
				break;
			default:
				break;
			}
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
	size_t componentCount = colliderManager->getComponentCount();

	for (size_t i = 0; i < componentCount; i++) {
		Collider* currentCollider = colliderManager->getComponentWithIndex(i);

		if (this->playerMovement->getEntity().uid == currentCollider->getEntity().uid) {
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
	size_t colliderCount = colliderManager->getComponentCount();

	if(playerMovement != nullptr) {
		size_t collisionCounter = 0;

		Position* currentPosition = positionManager->getComponent(this->playerMovement->getEntity());
		Collider* currentCollider = colliderManager->getComponent(this->playerMovement->getEntity());

		if (currentCollider == nullptr) {
			return;
		}

		if (currentCollider->isActive()) {
			for (size_t z = 0; z < colliderCount; z++)
			{
				Collider* nextCollider = colliderManager->getComponentWithIndex(z);

				if (nextCollider->isActive()) {
					// check if both entities
					if (nextCollider->getEntity().uid != this->playerMovement->getEntity().uid) {
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