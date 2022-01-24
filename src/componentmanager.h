#pragma once
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
	 * @return Added component of entity. Returns nullptr on failure.
	*/
	Component* addComponent(Entity e) {
		if (currentIndex < maxIndex) {
			entityIndexMap[e] = currentIndex;
			currentIndex++;
			return &componentData[currentIndex - 1];
		}
		return nullptr;
	}
	/**
	 * @brief Gets the component of given entity.
	 * @param e - Entity to get the component from.
	 * @return The component of entity. Returns nullptr on failure.
	*/
	Component* getComponent(Entity e) {
		if (entityIndexMap.count(e) > 0) {
			size_t idx = entityIndexMap[e];
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
		size_t deleteIdx = entityIndexMap[e];
		entityIndexMap.erase(e);

		if (deleteIdx != currentIndex - 1) {
			Entity endEntity;

			for (auto& i : entityIndexMap) {
				if (i.second == currentIndex - 1) {
					endEntity = i.first;
					break;
				}
			}

			componentData[deleteIdx] = componentData[currentIndex - 1];
			entityIndexMap[endEntity] = deleteIdx;
		}
		currentIndex--;
	}

	/**
	 * @brief Debug function to list every entitiy -> index mapping.
	 * Should not be used in final project.
	*/
	void DebugListEntityIndexMap() {
		std::map<Entity, size_t>::iterator itr;
		for (itr = entityIndexMap.begin(); itr != entityIndexMap.end(); itr++) {
			Entity temp = itr->first;
			std::cout <<temp.uid << " -> " << itr->second << std::endl;
		}
	}

	/**
	 * @brief Returns the component with given index.
	 * @param idx - index of component. Returns nullptr on failure.
	*/
	Component* getComponentWithIndex(size_t idx) {
		if (idx < maxIndex) {
			return &componentData[idx];
		}
		return nullptr;
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
	std::map<Entity, size_t> entityIndexMap;
	/**
	* @brief Array of components.
	*/
	std::array<Component, 1024> componentData;
	/**
	* @brief Next free index of componentData array.
	*/
	size_t currentIndex = 0;

	/**
	 * @brief Maximum number of components
	*/
	size_t maxIndex = 1024;
};