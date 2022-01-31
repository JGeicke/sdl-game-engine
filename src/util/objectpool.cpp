#include "objectpool.h"
/**
* @brief Initializes the objects in the pool.
* @param entityTag - Tag of the entities in the pool.
*/
void ObjectPool::init(const char* entityTag) {
	for (size_t i = 0; i < POOL_SIZE; i++)
	{
		entites[i] = this->entityManager->createEntity(entityTag, true);
		Position* pos = this->positionManager->addComponent(entites[i]);
		if (pos != nullptr) {
			pos->setEntity(entites[i]);
			pos->setPosition(0,0);
		}
		else {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Entity Initialization error", "Could not add position component to entity in object pool.", NULL);
		}
	}
}

/**
* @brief Gets the next free object in the pool.
* @return Next free entity in the pool.
*/
Entity ObjectPool::getNext() {
	Entity result = { 0,"", false };
	for (size_t i = 0; i < POOL_SIZE; i++)
	{
		if (!usedEntites[i]) {
			result = entites[i];
			usedEntites[i] = true;
			break;
		}
	}

	if (result.uid == 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Object Pool error", "No free entity in object pool.", NULL);
	}

	return result;
}

/**
* @brief Collects object in pool that is no longer needed.
* @param e - Entity to collect.
* @return Whether the object was succesfully collected.
*/
bool ObjectPool::collect(Entity e) {
	for (size_t i = 0; i < POOL_SIZE; i++)
	{
		if (entites[i].uid == e.uid) {
			// reset 
			this->positionManager->getComponent(e)->setPosition(0, 0);
			usedEntites[i] = false;
			return true;
		}
	}
	return false;
}