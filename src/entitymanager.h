#pragma once
#include "entity.h"
#include <unordered_set>

/**
 * @brief Struct with hash function for the entities hashset.
*/
struct Hash {
	/**
	 * @brief Hash function for entities. Returns the uid of the entity as the hash.
	 * @param entity - Entity to hash.
	 * @return Hash of the entity.
	*/
	size_t operator() (const Entity& entity) const {
		return entity.uid;
	}
};

/**
 * @brief Class to manage the game entities. Objects are able to create/delete entities and are able to check whether an entity does still exist.
*/
class EntityManager {
public:
	/**
	 * @brief Create new entity object.
	 * @param tag - Tag of entity
	 * @param isPreserved -  Whether the entity is preserved across scenes.
	 * @return Pointer to created entity.
	*/
	Entity createEntity(const char* tag, bool isPreserved);
	/**
	 * @brief Check if the entity is still alive.
	 * @param e - Entity to check
	 * @return Whether entity e still exists.
	*/
	bool hasEntity(Entity e);
	/**
	 * @brief Destroys the entity.
	 * @param e - Entity to destroy.
	*/
	void destroyEntity(Entity e);

	/**
	 * @brief Debug function to list currently existing entities.
	 * Should not be used in final project.
	*/
	void debugListEntities();

	/**
	 * @brief Gets iterator to the beginning of the entity set.
	 * @return Iterator to the beginning of the entity set.
	*/
	std::unordered_set<Entity>::iterator getEntityBegin() {
		return entities.begin();
	}

	/**
	 * @brief Gets iterator to the end of the entity set.
	 * @return Iterator to the end of the entity set.
	*/
	std::unordered_set<Entity>::iterator getEntityEnd() {
		return entities.end();
	}

	~EntityManager(){}
private:
	/**
	 * @brief Hashset with every existing entity.
	*/
	std::unordered_set<Entity, Hash> entities;
	/**
	 * @brief Next entity to be created.
	*/
	Entity next = { 0 };
};