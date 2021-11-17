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
	*/
	PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager,
		ComponentManager<Position>* positionManager, ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager);

	/**
	 * @brief Physic system update loop.
	*/
	virtual void update();
private:
	/**
	 * @brief Reference to input manager to use the user input.
	*/
	InputManager* inputManager;
	/**
	 * @brief Reference to the movement manager to gain access to movement components.
	*/
	ComponentManager<Movement>* movementManager;

	/**
	 * @brief Reference to the position manager to gain acess to position components.
	*/
	ComponentManager<Position>* positionManager;

	/**
	 * @brief Reference to the sprite manager to be able to flip the sprites.
	*/
	ComponentManager<Sprite>* spriteManager;

	/**
	 * @brief Reference to the animator manager to be able to adjust animation based physics.
	*/
	ComponentManager<Animator>* animatorManager;
};