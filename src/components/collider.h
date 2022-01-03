#pragma once
#include "basecomponent.h"
#include <iostream>
#include "SDL.h"
/**
 * @brief Collider component. A collider is needed for collision between entities in the gameworld.
*/
struct Collider : BaseComponent {
	// function pointer
	typedef void (*eventFunction)(Collider*, Collider*);
public:
	/**
	 * @brief Prints the collider component.
	*/
	void print() {
		std::cout << "Collider (Entity: " << entity.uid << ") is Trigger: " << isColliderTrigger << std::endl;
	}

	/**
	 * @brief Initializes the collider.
	 * @param x - X position of the entity. Needed for non moving entites.
	 * @param y - Y position of the entity. Needed for non moving entities.
	 * @param offsetX - X offset of the collider.
	 * @param offsetY - Y offset of the collider.
	 * @param w - Width of the collider.
	 * @param h - Height of the collider.
	 * @param isTrigger - Whether the collider is a trigger.
	*/
	void init(int x, int y, int offsetX, int offsetY, int w, int h, bool isTrigger) {
		isColliderTrigger = isTrigger;
		size.x = w;
		size.y = h;

		offset.x = offsetX;
		offset.y = offsetY;

		colliderRect.w = w;
		colliderRect.h = h;

		colliderRect.x = (x-(w/2))+offsetX;
		colliderRect.y = (y-(h/2))+offsetY;
	}

	/**
	 * @brief Gets the offset of the collider.
	 * @return Pointer to the offset of the collider.
	*/
	SDL_Point* getColliderOffset() {
		return &offset;
	}

	/**
	 * @brief Gets the size of the collider.
	 * @return Pointer to the size of the collider.
	*/
	SDL_Point* getColliderSize() {
		return &size;
	}

	/**
	 * @brief Checks if the collider is a trigger.
	 * @return Whether the collider is a trigger.
	*/
	bool isTrigger() {
		return isColliderTrigger;
	}
	
	/**
	 * @brief Sets the size of the collider.
	 * @param size - New size of the collider.
	*/
	void setColliderSize(SDL_Point size) {
		this->size = size;
		colliderRect.w = size.x;
		colliderRect.h = size.y;
	}

	/**
	 * @brief Sets the offset of the collider relativ to the entity position.
	 * @param offset - New offset of collider.
	*/
	void setColliderOffset(SDL_Point offset) {
		this->offset = offset;
	}

	/**
	 * @brief Sets the collider to be a trigger.
	 * @param triggerCollider - Whether the collider is a trigger.
	*/
	void setTrigger(bool isTrigger) {
		isColliderTrigger = isTrigger;
	}

	/**
	 * @brief Gets the collider rectangle used for collision.
	 * @return Pointer to the collider rectangle.
	*/
	SDL_Rect* getColliderRect() {
		return &colliderRect;
	}

	/**
	 * @brief Sets the position of the collider rectangle.
	 * @param x - New x position.
	 * @param y - New y position.
	*/
	void setColliderRect(int x, int y) {
		colliderRect.x = x;
		colliderRect.y = y;
	}

	/**
	 * @brief Adds a trigger enter function.
	 * @param triggerFunction - Function to call when trigger collides with another entity collider.
	*/
	void onTriggerEnter(eventFunction triggerFunction) {
		hasTriggerEnterFunction = true;
		onTriggerEnterFunction = triggerFunction;
	}

	/**
	 * @brief Adds a collision enter function.
	 * @param collisionFunction - Function to call when collider collides with another entity collider.
	*/
	void onCollisionEnter(eventFunction collisionFunction) {
		hasCollisionEnterFunction = true;
		onCollisionEnterFunction = collisionFunction;
	}

	/**
	 * @brief Adds a trigger stay function.
	 * @param triggerFunction - Function to call when trigger collides with another entity collider.
	*/
	void onTriggerStay(eventFunction triggerFunction) {
		hasTriggerStayFunction = true;
		onTriggerStayFunction = triggerFunction;
	}

	/**
	 * @brief Adds a collision stay function.
	 * @param collisionFunction - Function to call when collider collides with another entity collider.
	*/
	void onCollisionStay(eventFunction collisionFunction) {
		hasCollisionStayFunction = true;
		onCollisionStayFunction = collisionFunction;
	}

	/**
	 * @brief Executes the on collision behaviour depending on if the collider is a trigger or a normal collider.
	 * @param collisionComponent - Collision component this collider collided with.
	*/
	void collision(Collider* collisionComponent) {
		if (lastCollision.uid == collisionComponent->getEntity().uid) {
			if (isColliderTrigger) {
				if (hasTriggerStayFunction) {
					onTriggerStayFunction(this, collisionComponent);
				}
			}
			else {
				if (hasCollisionStayFunction) {
					onCollisionStayFunction(this, collisionComponent);
				}
			}
		}
		else {
			if (isColliderTrigger) {
				if (hasTriggerEnterFunction) {
					onTriggerEnterFunction(this, collisionComponent);
				}
			}
			else {
				if (hasCollisionEnterFunction) {
					onCollisionEnterFunction(this, collisionComponent);
				}
			}
			lastCollision = collisionComponent->getEntity();
			collisionComponent->lastCollision = this->entity;
		}
	}

	/**
	 * @brief Resets last collision. This function is used when no collision occured this frame with this collider.
	*/
	void resetLastCollision() {
		lastCollision = { 0 };
	}

	/**
	 * @brief Gets last collision. This function is used to be able to reset last collision of static entities (non-moving).
	 * @return The entity of the last collider this collider collided with.
	*/
	Entity getLastCollision() {
		return lastCollision;
	}
private:
	/**
	 * @brief Rectangle collider that determines position and size.
	*/
	SDL_Rect colliderRect = {0,0,0,0};
	/**
	 * @brief Position offset of the collider relativ to the entity position.
	*/
	SDL_Point offset = {0,0};
	/**
	 * @brief Width/Height of the collider.
	*/
	SDL_Point size = { 0,0 };
	/**
	 * @brief Whether the collider is a trigger. Trigger colliders do not block movement and interact differently.
	*/
	bool isColliderTrigger = false;

	/**
	 * @brief Handler function when another collider first collides with this trigger collider.
	*/
	eventFunction onTriggerEnterFunction = NULL;
	/**
	 * @brief Whether the collider has a trigger enter handler function.
	*/
	bool hasTriggerEnterFunction = false;

	/**
	 * @brief Handler function when another collider first collides with this collider.
	*/
	eventFunction onCollisionEnterFunction = NULL;
	/**
	 * @brief Whether the collider has a collision enter handler function.
	*/
	bool hasCollisionEnterFunction = false;

	/**
	 * @brief Handler function for the ongoing collision of the trigger collider with another collider.
	*/
	eventFunction onTriggerStayFunction = NULL;
	/**
	 * @brief Whether the trigger collider has a trigger stay function for the ongoing collision with another collider.
	*/
	bool hasTriggerStayFunction = false;
	
	/**
	 * @brief Handler function for the ongoing collision of the collider with another collider.
	*/
	eventFunction onCollisionStayFunction = NULL;
	/**
	 * @brief Whether the collider has a collision stay function for the ongoing collision with another collider.
	*/
	bool hasCollisionStayFunction = false;

	/**
	 * @brief Entity of the last collider this collider collided with.
	*/
	Entity lastCollision = { 0 };
};