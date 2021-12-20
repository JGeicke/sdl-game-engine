#pragma once
#include "../entity.h"
#include "../entitymanager.h"
#include "../componentmanager.h"
#include "../components/position.h"
#include "SDL.h"
/**
 * @brief Object(Entity) pool of precreated objects. Can be used to avoid the overhead of creating/destroying objects.
*/
class ObjectPool {
public:
	/**
	 * @brief Creates an object pool.
	 * @param entityMngr - Pointer to the entity manager.
	 * @param positionMngr - Pointer to the position component manager.
	*/
	ObjectPool(EntityManager* entityMngr, ComponentManager<Position>* positionMngr) :entityManager{ entityMngr }, positionManager{positionMngr} {}

	/**
	 * @brief Initializes the objects in the pool.
	 * @param entityTag - Tag of the entities in the pool.
	*/
	void init(const char* entityTag);

	/**
	 * @brief Gets the next free object in the pool.
	 * @return Next free entity in the pool.
	*/
	Entity getNext();

	/**
	 * @brief Collects object in pool that is no longer needed.
	 * @param e - Entity to collect.
	 * @return Whether the object was succesfully collected.
	*/
	bool collect(Entity e);
	/**
	 * @brief Gets the size of the object pool.
	 * @return Size of the object pool.
	*/
	int getPoolSize() { return POOL_SIZE; }
	/**
	 * @brief Gets an object with an pool index.
	 * @param idx - Index of entity.
	 * @return Entity with pool index.
	*/
	Entity getEntityByIndex(int idx) {
		return entites[idx];
	}

	/**
	 * @brief Checks if object with given pool index is currently used.
	 * @param idx - Index of entity.
	 * @return Whether the object with the pool index is currently used.
	*/
	bool isEntityUsed(int idx) {
		return usedEntites[idx];
	}
private:
	/**
	 * @brief Size of object pool.
	*/
	static const int POOL_SIZE = 100;
	/**
	 * @brief Array with objects/entites in the pool.
	*/
	Entity entites [POOL_SIZE];
	/**
	 * @brief Array that tracks which object/entity is currently used.
	*/
	bool usedEntites[POOL_SIZE] = { false };

	/**
	 * @brief Pointer to the entity manager.
	*/
	EntityManager* entityManager;
	/**
	 * @brief Pointer to the position component manager.
	*/
	ComponentManager<Position>* positionManager;
};