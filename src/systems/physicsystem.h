#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
#include "../inputmanager.h"

class PhysicSystem : GameSystem {
public:
	PhysicSystem(InputManager* inputManager, ComponentManager<Movement>* movementManager, ComponentManager<Position>* positionManager);
	virtual void update();
private:
	InputManager* inputManager;
	ComponentManager<Movement>* movementManager;
	ComponentManager<Position>* positionManager;
};