#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
#include "../inputmanager.h"

/**
 * @brief Physic System to simulate moving objects in the game world.
*/
class PhysicSystem : GameSystem {
public:
	/**
	 * @brief Constructor of physic system to set needed references.
	 * @param inputManager - Input manager to handle user inputs.
	 * @param movementManager - Movement Manager to gain access to movement components.
	 * @param positionManager - Position manager to gain access to position components.
	 * @param spriteManager - Sprite manager to access to sprite components.
	 * @param animatorManager - Animator manager to access animator components.
	 * @param colliderManager - Collider manager to access collider components for collisions.
	*/
	PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager, ComponentManager<Position>* positionManager,
		ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager, ComponentManager<Collider>* colliderManager);

	/**
	 * @brief Physic system update loop.
	*/
	virtual void update();
private:
	/**
	 * @brief Pointer to input manager to use the user input.
	*/
	InputManager* inputManager;
	/**
	 * @brief Pointer to the movement manager to gain access to movement components.
	*/
	ComponentManager<Movement>* movementManager;

	/**
	 * @brief Pointer to the position manager to gain acess to position components.
	*/
	ComponentManager<Position>* positionManager;

	/**
	 * @brief Pointer to the sprite manager to be able to flip the sprites.
	*/
	ComponentManager<Sprite>* spriteManager;

	/**
	 * @brief Pointer to the animator manager to be able to adjust animation based physics.
	*/
	ComponentManager<Animator>* animatorManager;

	/**
	 * @brief Pointer to the collider manager to be able to handle collision between entities.
	*/
	ComponentManager<Collider>* colliderManager;

	/**
	 * @brief Handles the player movement each frame.
	*/
	void handlePlayerMovement();

	/**
	 * @brief Handles collision between entities.
	*/
	void handleCollision();

	/**
	 * @brief Calculates the positions of the colliders.
	*/
	void calculateColliderPositions();

	/**
	 * @brief Adjusts the position of the collider based on the position.
	*/
	void adjustColliderPosition(Collider* collider,Position* position);

	/**
	 * @brief Detects collisions between colliders.
	*/
	void detectCollisions();
};