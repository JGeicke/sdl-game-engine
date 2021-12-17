#include "entitymanager.h"
#include <iostream>

/**
 * @brief Creates new entity with the next free uid.
 * @param tag - Tag of entity
 * @param isPreserved -  Whether the entity is preserved across scenes.
 * @return Copy of created entity.
*/
Entity EntityManager::createEntity(const char* tag, bool isPreserved) {
	next.uid++;
	std::cout << "\n+++++++++++++++Start uid:+++++++++++++++++++\n";
	std::cout << next.uid;
	while (hasEntity(next)) {
		next.uid++;
	}
	next.tag = tag;
	next.preserve = isPreserved;
	std::cout << "\n+++++++++++++++Selected uid:+++++++++++++++++++\n";
	std::cout << next.uid << "\n";
	entities.insert(next);
	return next;
}

/**
 * @brief Checks if the entity still exists in the hashset.
 * @param e - Entity to check
 * @return Whether the entity still exists or not.
*/
bool EntityManager::hasEntity(Entity e) {
	return (entities.count(e)==1) ? true : false;
}

/**
 * @brief Removes the entity from the hashset.
 * @param e - Entity to remove
*/
void EntityManager::destroyEntity(Entity e) {
	entities.erase(e);
}

/**
* @brief Debug function to list currently existing entities.
* Should not be used in final project.
*/
void EntityManager::debugListEntities() {
	std::cout << "\n++++++++++++++++++ENTITIY LIST+++++++++++++++++++\n";
	for (auto itr = entities.begin(); itr != entities.end(); ++itr) {
		std::cout << "Entity UID " << itr->uid << std::endl;
	}
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n" << std::endl;
}	