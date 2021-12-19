#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
#include "../inputmanager.h"
#include <cmath>

/**
 * @brief Physic System to simulate moving objects in the game world.
*/
class PhysicSystem : public GameSystem {
public:
	/**
	 * @brief Constructor of physic system to set needed references.
	 * @param inputManager - Input manager to handle user inputs.
	 * @param playerMovement - Movement component of player.
	 * @param positionManager - Position manager to gain access to position components.
	 * @param spriteManager - Sprite manager to access to sprite components.
	 * @param animatorManager - Animator manager to access animator components.
	 * @param colliderManager - Collider manager to access collider components for collisions.
	 * @param progManager - Projectile movement manager to access the projectile movement components.
	*/
	PhysicSystem(InputManager* inputManager, Movement* playerMovement, ComponentManager<Position>* positionManager,
		ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager, ComponentManager<Collider>* colliderManager,
		ComponentManager<ProjectileMovement>* projManager);

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
	 * @brief Pointer to the movement component of the player.
	*/
	Movement* playerMovement;

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
	 * @brief Projectile movement manager to be able to handle the movement of projectiles.
	*/
	ComponentManager<ProjectileMovement>* projManager;

	/**
	 * @brief Handles the player movement each frame.
	*/
	void handlePlayerMovement();

	/**
	 * @brief Controls the animation states of the player.
	*/
	void controlPlayerAnimationStates();

	/**
	 * @brief Handles the movement of projectiles.
	*/
	void handleProjectileMovement();

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