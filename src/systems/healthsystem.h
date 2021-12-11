#pragma once
#include "gamesystem.h"
#include "../components/components.h"
#include "../componentmanager.h"

class HealthSystem :public GameSystem {
public:
	HealthSystem(ComponentManager<Health>* healthManager);
	~HealthSystem();
	/**
	 * @brief Health system update loop.
	*/
	virtual void update();
private:
	ComponentManager<Health>* healthManager = nullptr;
};