#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "entity.h"
#include <map>
#include <iostream>
template <typename Component>
class ComponentManager{
public:
	void addComponent(Entity e) {
		// componentData[currentIndex] = new Component(); 
		std::cout << "created component for entity with index " << currentIndex << std::endl;
		entityIndexMap[e] = currentIndex;
		currentIndex++;
	}
	Component* getComponent(Entity e) {
		if (entityIndexMap.count(e) > 0) {
			unsigned int idx = entityIndexMap[e];
			std::cout << "found index for component:" << idx << std::endl;
			return &componentData[idx];
		}
		else {
			return nullptr;
		}
	}
	void removeComponent(Entity e) {
		unsigned int deleteIdx = entityIndexMap[e];
		std::map<Entity, unsigned>::iterator endItr = entityIndexMap.end();
		--endItr;
		Entity endEntity = endItr->first;
		unsigned int endIdx = endItr->second;

		entityIndexMap.erase(e);
		if (e != endEntity) {
			// entity is not last in map
			componentData[deleteIdx] = componentData[endIdx];
			entityIndexMap[endEntity] = deleteIdx;
		}
		currentIndex--;
	}
	void DebugListEntityIndexMap() {
		std::map<Entity, unsigned>::iterator itr;
		for (itr = entityIndexMap.begin(); itr != entityIndexMap.end(); itr++) {
			Entity temp = itr->first;
			std::cout <<temp.uid << " -> " << itr->second << std::endl;
		}
	}
private:
	std::map<Entity, unsigned> entityIndexMap;
	Component componentData[1024] = {};
	unsigned int currentIndex = 0;
};
#endif // !COMPONENTMANAGER_H