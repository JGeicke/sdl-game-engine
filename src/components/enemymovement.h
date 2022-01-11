#pragma once
#include "basecomponent.h"
#include <iostream>
#include <vector>
#include <queue>
template<typename T, typename priority>
struct PriorityQueue {
	typedef std::pair<priority, T> Element;
	std::priority_queue<Element, std::vector<Element>, std::greater<Element>> elements;

	inline bool empty(){
		return elements.empty();
	}	


	inline void put(T item, priority prio) {
		elements.emplace(prio, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

/**
 * @brief Struct representing the logical position on the tilemap grid.
*/
struct Node {
	/**
	 * @brief X-position on the grid.
	*/
	int x = 0;
	/**
	 * @brief Y-position on the grid.
	*/
	int y = 0;
	/**
	 * @brief Parentnode. A parent is the node used to reach this node when searching for a path. Needed to backtrack the found path.
	*/
	Node* parent = nullptr;
	/**
	 * @brief Whether the node was visited during pathfinding.
	*/
	bool visited = false;
	/**
	 * @brief Whether the node is an obstacle.
	*/
	bool obstacle = false;
	/**
	 * @brief Neighbournodes.
	*/
	std::vector<Node*> neighbours;

	/**
	* @brief Current gCost of the node. Total cost from start to this node.
	*/
	float gcost = 0.0f;

	/**
	* @brief Current fCost of the node. Total cost from start to this node (gcost) plus an estimate of the remaining distance to the destination.
	*/
	float fcost = 0.0f;
};

/**
 * @brief Component to hold the attributes used for enemy movement.
*/
struct EnemyMovement : BaseComponent {
public:
	/**
	 * @brief Prints the enemy movement component.
	*/
	void print() {
		std::cout << "Enemy Movement (Entity: " << entity.uid << ") Movement speed: " << movementSpeed << std::endl;
	}

	/**
	 * @brief Gets the enemy movement speed.
	 * @return Enemy movement speed.
	*/
	float getMovementSpeed() { return movementSpeed; }
	/**
	 * @brief Sets the enemy movement speed.
	 * @param mspeed - New enemy movement speed.
	*/
	void setMovementSpeed(float mspeed) { this->movementSpeed = mspeed; }

	/**
	 * @brief Gets the current movement destination of the enemy.
	 * @return Pointer to the current destination node.
	*/
	Node* getDestination() { return destination; }
	/**
	 * @brief Sets the current movement destination node.
	 * @param newDest - New movement destination node.
	*/
	void setDestination(Node* newDest) {
		destination = newDest;
	}

	/**
	 * @brief Sets the route to the destination node calculated with a*.
	 * @param route - Route to the destination node.
	*/
	void setRoute(std::vector<Node*> route) {
		this->route = route;
		this->nextNodeIndex = route.size()-2;
	}

	/**
	 * @brief Gets the current route to the destination node.
	 * @return Vector containing the nodes on the route to the current destination node.
	*/
	std::vector<Node*> getRoute() {
		return route;
	}

	/**
	 * @brief Increases the pathfinding timer. Used to avoid calculating the path every frame.
	 * @param increase - Timer increase (milliseconds between movement simulation).
	*/
	void increaseTimer(int increase) {
		currentTimer += increase;
		if (currentTimer >= timerBase) {
			flag(true);
		}
	}

	/**
	 * @brief Flags the enemy movement component for pathfinding.
	 * @param flag - Whether the physic system should calculate a new path for the enemy movement component.
	*/
	void flag(bool flag) {
		calcRoute = flag;
		if (!calcRoute) {
			currentTimer = 0;
		}
	}

	/**
	 * @brief Checks if the component is flagged for pathfinding.
	 * @return  Whether the physic system should calculate a new path for the enemy movement component.
	*/
	bool isFlagged() { return calcRoute; }

	/**
	 * @brief Gets the next node on the route.
	 * @return Pointer to the next node on the route.
	*/
	Node* getNextNode() {
		return route[nextNodeIndex];
	}

	bool hasNextNode() {
		return nextNodeIndex >= 0 && route.size() > 0;
	}

	/**
	 * @brief Checks if the enemy arrived at the next node on the route based on the current position.
	 * @param x - Current x position of the enemy.
	 * @param y - Current y position of the enemy.
	 * @return Whether the enemy arrived at the next node on the route.
	*/
	bool arrivedAtNextNode(int x, int y) {
		if (nextNodeIndex >= 0 && route.size() > 0) {
			return (x == route[nextNodeIndex]->x && y == route[nextNodeIndex]->y) ? true : false;
		}
		return true;
	}

	/**
	 * @brief Selects the next node of the route. If there is no next node (= current node is destination), remove the current destination.
	*/
	void setNextNode() {
		if (nextNodeIndex > 0) {
			nextNodeIndex -= 1;
		}
		else {
			destination = nullptr;
		}
	}

	/**
	 * @brief Sets the pathfinding timer. This determins how often the path is calculated.
	 * @param timerMS - New pathfinding timer.
	*/
	void setPathfindingTimer(int timerMS) {
		this->timerBase = timerMS;
	}

	/**
	 * @brief Sets current target entity.
	 * @param e - New target entity.
	*/
	void setTarget(Entity e) {
		this->target = e;
	}

	/**
	 * @brief Checks if the component has a target entity.
	 * @return Whether the component has a target entity.
	*/
	bool hasTarget() {
		return this->target.uid != 0;
	}

	/**
	 * @brief Resets the current target entity.
	*/
	void resetTarget() {
		this->target = { 0, "", false};
	}

	/**
	 * @brief Gets the current target entity.
	 * @return The current target entity.
	*/
	Entity getTarget() {
		return this->target;
	}

	/**
	 * @brief Sets the maximum distance to the target.
	 * @param distance - New maximum distance to the target.
	*/
	void setMaxDistance(int distance) {
		this->maxDistance = distance;
	}

	/**
	 * @brief Gets the max distance to the target.
	 * @return Max distance.
	*/
	int getMaxDistance() {
		return this->maxDistance;
	}
private:
	/**
	 * @brief Base timer between pathfindings.
	*/
	int timerBase = 3000;
	/**
	 * @brief Current timer.
	*/
	int currentTimer = 0;
	/**
	 * @brief Whether the component is flagged for pathfinding.
	*/
	bool calcRoute = true;

	/**
	 * @brief Enemy movement speed.
	*/
	float movementSpeed = 0.0f;

	/**
	 * @brief Current target entity.
	*/
	Entity target = { 0, "", false };

	/**
	 * @brief Max distance to target.
	*/
	int maxDistance = 10;

	/**
	 * @brief Pointer to the current movement destination node.
	*/
	Node* destination = nullptr;
	/**
	 * @brief Index to the next node of the route.
	*/
	int nextNodeIndex = 0;
	/**
	 * @brief Current route to the destination node.
	*/
	std::vector<Node*> route;
};