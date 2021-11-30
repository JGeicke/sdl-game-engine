#pragma once
#include "basecomponent.h"
#include "SDL.h"
/**
 * @brief Collider component. A collider is needed for collision between entities in the gameworld.
*/
struct Collider : BaseComponent {
public:
	/**
	 * @brief Prints the collider component.
	*/
	void print() {
		// TODO: print collider
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
private:
	SDL_Rect colliderRect;
	SDL_Point offset;
	SDL_Point size;
	bool isColliderTrigger;
};