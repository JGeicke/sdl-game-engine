#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "entity.h"
#include <map>
#include <array>
#include <iostream>
/**
 * @brief Template class for ComponentManagers. Each ComponentManager manages a specific component type.
 * @tparam Component - The component type to manage.
*/
template <typename Component>
class ComponentManager{
public:
	/**
	 * @brief Adds the component type to the entity and returns added component.
	 * @param e - Entity to add the component to.
	 * @return Added component of entity.
	*/
	Component* addComponent(Entity e) {
		//REMOVE: std::cout << "created component for entity with index " << currentIndex << std::endl;
		entityIndexMap[e] = currentIndex;
		currentIndex++;
		return &componentData[currentIndex - 1];
	}
	/**
	 * @brief Gets the component of given entity.
	 * @param e - Entity to get the component from.
	 * @return The component of entity.
	*/
	Component* getComponent(Entity e) {
		if (entityIndexMap.count(e) > 0) {
			unsigned int idx = entityIndexMap[e];
			//REMOVE: std::cout << "found index for component:" << idx << std::endl;
			return &componentData[idx];
		}
		else {
			return nullptr;
		}
	}

	/**
	 * @brief Remove the component of the entity.
	 * @param e - Entity to remove the component from.
	*/
	void removeComponent(Entity e) {
		unsigned int deleteIdx = entityIndexMap[e];
		std::map<Entity, unsigned>::iterator endItr = entityIndexMap.end();
		--endItr;
		Entity endEntity = endItr->first;
		unsigned int endIdx = endItr->second;

		entityIndexMap.erase(e);
		if (e != endEntity) {
			/* entity is not last in map */
			componentData[deleteIdx] = componentData[endIdx];
			entityIndexMap[endEntity] = deleteIdx;
		}
		currentIndex--;
	}

	/**
	 * @brief Debug function to list every entitiy -> index mapping.
	 * Should not be used in final project.
	*/
	void DebugListEntityIndexMap() {
		std::map<Entity, unsigned>::iterator itr;
		for (itr = entityIndexMap.begin(); itr != entityIndexMap.end(); itr++) {
			Entity temp = itr->first;
			std::cout <<temp.uid << " -> " << itr->second << std::endl;
		}
	}

	/**
	 * @brief Returns the component with given index.
	 * @param idx - index of component.
	*/
	Component* getComponentWithIndex(size_t idx) {
		return &componentData[idx];
	}

	/**
	* @brief Returns current component count.
	* @return Current component count.
	*/
	size_t getComponentCount() {
		return currentIndex;
	}

	/**
	 * @brief Checks if entity has component.
	 * @param e - Entity to check
	 * @return Whether entity has component.
	*/
	bool hasComponent(Entity e) {
		return (entityIndexMap.count(e) > 0) ? true : false;
	}
private:
	/**
	 * @brief Mapping of entity to the index of the entity component in componentData.
	*/
	std::map<Entity, unsigned> entityIndexMap;
	/**
	* @brief Array of components.
	*/
	std::array<Component, 1024> componentData;
	/**
	* @brief Next free index of componentData array.
	*/
	size_t currentIndex = 0;
};
#endif // !COMPONENTMANAGER_H