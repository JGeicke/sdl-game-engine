#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
#include "../inputmanager.h"
#include <cmath>
#include <list>

/**
 * @brief Physic System to simulate moving objects in the game world.
*/
class PhysicSystem : public GameSystem {
public:
	/**
	 * @brief Constructor of physic system to set needed references.
	 * @param inputManager - Input manager to handle user inputs.
	 * @param playerMovement - Movement component of player.
	 * @param positionManager - Position manager to gain access to position components.
	 * @param spriteManager - Sprite manager to access to sprite components.
	 * @param animatorManager - Animator manager to access animator components.
	 * @param colliderManager - Collider manager to access collider components for collisions.
	 * @param progManager - Projectile movement manager to access the projectile movement components.
	 * @param enemyMovementManager - Enemy movement manager to be able to visually debug the pathing of enemies.
	*/
	PhysicSystem(InputManager* inputManager, Movement* playerMovement, ComponentManager<Position>* positionManager,
		ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager, ComponentManager<Collider>* colliderManager,
		ComponentManager<ProjectileMovement>* projManager, ComponentManager<EnemyMovement>* enemyMovementManager);

	/**
	 * @brief Physic system update loop.
	*/
	virtual void update();

	/**
	 * @brief Initializes the grid for the physic system.
	 * @param row - Number of rows.
	 * @param col - Number of cols.
	 * @param tileSize - Size of the tiles.
	 * @param tilesPerRow - Tiles per row.
	*/
	void initGrid(int row, int col, SDL_Point tileSize, int tilesPerRow);

	/**
	 * @brief Gets the current Node based on the position.
	 * @param pos - Position to get the current node off.
	 * @return Current Node.
	*/
	Node* getCurrentNode(Position* pos);

	/**
	 * @brief Gets the current Node based on the position.
	 * @param pos - Position to get the current node off.
	 * @return Current Node.
	*/
	Node* getCurrentNode(SDL_Point pos);

	/**
	 * @brief Sets the current camera zoom values.
	 * @param cameraZoomX - Current camera x zoom.
	 * @param cameraZoomY - Current camera y zoom.
	*/
	void setCameraZoom(float cameraZoomX, float cameraZoomY) {
		this->cameraZoomX = cameraZoomX;
		this->cameraZoomY = cameraZoomY;
	}
private:
	Node* nodes = nullptr;
	size_t nodeCount = 0;

	/**
	 * @brief Pointer to input manager to use the user input.
	*/
	InputManager* inputManager;
	/**
	 * @brief Pointer to the movement component of the player.
	*/
	Movement* playerMovement;

	/**
	 * @brief Pointer to the position manager to gain acess to position components.
	*/
	ComponentManager<Position>* positionManager;

	/**
	 * @brief Pointer to the sprite manager to be able to flip the sprites.
	*/
	ComponentManager<Sprite>* spriteManager;

	/**
	 * @brief Pointer to the animator manager to be able to adjust animation based physics.
	*/
	ComponentManager<Animator>* animatorManager;

	/**
	 * @brief Pointer to the collider manager to be able to handle collision between entities.
	*/
	ComponentManager<Collider>* colliderManager;

	/**
	 * @brief Projectile movement manager to be able to handle the movement of projectiles.
	*/
	ComponentManager<ProjectileMovement>* projManager;

	/**
	 * @brief Enemy movement manager to simulate enemy movement including pathfinding.
	*/
	ComponentManager<EnemyMovement>* enemyMovementManager;

	/**
	 * @brief Last timestamp of enemy movement simulation. Used to increase the pathfinding timers to the enemy movement components accordingly.
	*/
	Uint32 lastEnemyMovementTimestamp = 0;

	/**
	 * @brief Tilewidth of the current tilemap.
	*/
	int tileWidth=0;
	/**
	 * @brief Tileheight of the current tilemap.
	*/
	int tileHeight=0;
	/**
	 * @brief Number of columns in the current tilemap.
	*/
	size_t col=0;
	/**
	 * @brief Number of rows in the current tilemap.
	*/
	size_t row=0;
	/**
	 * @brief Tiles per row in the current tilemap.
	*/
	size_t tilesPerRow=0;

	/**
	 * @brief X zoom factor of camera.
	*/
	float cameraZoomX = 1.0f;

	/**
	 * @brief Y zoom factor of camera.
	*/
	float cameraZoomY = 1.0f;

	/**
	 * @brief Handles the player movement each frame.
	*/
	void handlePlayerMovement();

	/**
	 * @brief Controls the animation states of the an entity.
	 * @param e - Entity to control animation states off.
	 * @param direction - Direction of movement if present.
	 * @param checkMouseInput - Whether mouse input should be checked.
	*/
	void controlAnimationStates(Entity e, Vector2* direction, bool checkMouseInput);

	/**
	 * @brief Handles the movement of projectiles.
	*/
	void handleProjectileMovement();

	/**
	 * @brief Handles collision between entities.
	*/
	void handleCollision();

	/**
	 * @brief Calculates the positions of the colliders.
	*/
	void calculateColliderPositions();

	/**
	 * @brief Adjusts the position of the collider based on the position.
	*/
	void adjustColliderPosition(Collider* collider,Position* position);

	/**
	 * @brief Detects collisions between colliders.
	*/
	void detectCollisions();

	/**
	 * @brief Calculates the heuristic cost of the position to the destination.
	 * @param pos - Position to calculate the heuristic cost of.
	 * @param dest - Destination node.
	 * @return Heuristic cost from the position to the destination.
	*/
	float calculateHCost(Node* pos, Node* dest);

	/**
	 * @brief Marks nodes as obstacle when the match the collider positions.
	 * @param e - Entity to mark the obstacles for
	*/
	void markNodesAsObstacles(Entity e);

	/**
	 * @brief Calculates the path from the start node to the destination node using the a* algorithm.
	 * @param e - Entity to calculate path for.
	 * @param start - Startnode.
	 * @param dest - Destinationnode.
	 * @return Path from the start node to the destination node.
	*/
	std::vector<Node*> aStar(Entity e, Node* start, Node* dest);

	/**
	 * @brief Handles the movement of enemies.
	*/
	void handleEnemyMovement();

	/**
	 * @brief Marks node as obstacle.
	 * @param node - Node to mark as obstacle.
	*/
	void markNodeAsObstacle(Node* node);
};