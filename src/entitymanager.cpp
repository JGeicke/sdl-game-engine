#include "entitymanager.h"
#include <iostream>

Entity EntityManager::createEntity() {
	next.uid++;
	std::cout << "\n+++++++++++++++Start uid:+++++++++++++++++++\n";
	std::cout << next.uid;
	while (hasEntity(next)) {
		next.uid++;
	}
	std::cout << "\n+++++++++++++++Selected uid:+++++++++++++++++++\n";
	std::cout << next.uid;
	entities.insert(next);
	return next;
}
bool EntityManager::hasEntity(Entity e) {
	return (entities.count(e)==1) ? true : false;
}
void EntityManager::destroyEntity(Entity e) {
	entities.erase(e);
}

void EntityManager::debugListEntities() {
	std::cout << "\n++++++++++++++++++ENTITIY LIST+++++++++++++++++++\n";
	for (auto itr = entities.begin(); itr != entities.end(); ++itr) {
		std::cout << "Entity UID " << itr->uid << std::endl;
	}
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n";
}	