#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "entity.h"
#include <unordered_set>
struct Hash {
	size_t operator() (const Entity& entity) const {
		return entity.uid;
	}
};


class EntityManager {
public:
	Entity createEntity();
	bool hasEntity(Entity e);
	void destroyEntity(Entity e);
	void debugListEntities();
	~EntityManager(){}
private:
	std::unordered_set<Entity, Hash> entities;
	Entity next;
};
#endif // !ENTITYMANAGER_H
