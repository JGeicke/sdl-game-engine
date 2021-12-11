#include "healthsystem.h"

HealthSystem::HealthSystem(ComponentManager<Health>* healthManager){
	this->healthManager = healthManager;
}
HealthSystem::~HealthSystem(){}

/**
* @brief Health system update loop.
*/
void HealthSystem::update() {
	/*
	size_t componentCount = this->healthManager->getComponentCount();

	for (size_t i = 0; i < componentCount; i++)
	{

	}
	*/
}