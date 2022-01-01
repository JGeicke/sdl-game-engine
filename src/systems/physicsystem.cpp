#include "physicsystem.h"
/**
* @brief Constructor of physic system to set needed references.
* @param inputManager - Input manager to handle user inputs.
* @param playerMovement - Movement component of player.
* @param positionManager - Position manager to gain access to position components.
* @param spriteManager - Sprite manager to access to sprite components.
* @param animatorManager - Animator manager to access animator components.
* @param colliderManager - Collider manager to access collider components for collisions.
* @param progManager - Projectile movement manager to access the projectile movement components.
*/
PhysicSystem::PhysicSystem(InputManager* inputManager, Movement* playerMovement, ComponentManager<Position>* positionManager,
	ComponentManager<Sprite>* spriteManager, ComponentManager<Animator>* animatorManager, ComponentManager<Collider>* colliderManager,
	ComponentManager<ProjectileMovement>* projManager, ComponentManager<EnemyMovement>* enemyMovementManager) {
	this->inputManager = inputManager;
	this->playerMovement = playerMovement;
	this->positionManager = positionManager;
	this->spriteManager = spriteManager;
	this->animatorManager = animatorManager;
	this->colliderManager = colliderManager;
	this->projManager = projManager;
	this->enemyMovementManager = enemyMovementManager;
}

/**
* @brief Render system update loop. Iterates over every movement component and changes the position component of the same entity. 
*/
void PhysicSystem::update() {
	handleEnemyMovement();
	handlePlayerMovement();
	handleProjectileMovement();
	handleCollision();
}

/**
* @brief Initializes the grid for the physic system.
* @param row - Number of rows.
* @param col - Number of cols.
* @param tileSize - Size of the tiles.
* @param tilesPerRow - Tiles per row.
*/
void PhysicSystem::initGrid(int row, int col, SDL_Point tileSize, int tilesPerRow) {

	this->row = row;
	this->col = col;
	this->tileWidth = tileSize.x;
	this->tileHeight = tileSize.y;
	this->tilesPerRow = tilesPerRow;

	if (row < 1 || col < 1) {
		return;
	}

	nodes = new Node[row*col];
	for (size_t x = 0; x < row; x++)
	{
		for (size_t y = 0; y < col; y++)
		{
			nodes[y * row + x].x = x;
			nodes[y * row + x].y = y;
			nodes[y * row + x].visited = false;
			nodes[y * row + x].parent = nullptr;
			nodeCount++;
		}
	}

	// determine neighbours
	for (size_t x = 0; x < row; x++)
	{
		for (size_t y = 0; y < col; y++)
		{
			// left
			if (x > 0) {
				nodes[y * row + x].neighbours.push_back(&nodes[y * row + (x - 1)]);

				// top
				if (y > 0) {
					nodes[y * row + x].neighbours.push_back(&nodes[(y - 1) * row + (x-1)]);
				}

				//down
				if (y < (col - 1)) {
					nodes[y * row + x].neighbours.push_back(&nodes[(y + 1) * row + (x-1)]);
				}
			}

			// right
			if (x < (row - 1)) {
				nodes[y * row + x].neighbours.push_back(&nodes[y * row + (x + 1)]);

				// top
				if (y > 0) {
					nodes[y * row + x].neighbours.push_back(&nodes[(y - 1) * row + (x + 1)]);
				}

				//down
				if (y < (col - 1)) {
					nodes[y * row + x].neighbours.push_back(&nodes[(y + 1) * row + (x + 1)]);
				}
			}

			// top
			if (y > 0) {
				nodes[y * row + x].neighbours.push_back(&nodes[(y-1) * row + x ]);
			}

			//down
			if (y < (col) - 1) {
				nodes[y * row + x].neighbours.push_back(&nodes[(y + 1) * row + x]);
			}
		}
	}
}
/**
* @brief Handles the player movement each frame.
*/
void PhysicSystem::handlePlayerMovement() {
	if(playerMovement->getEntity().uid != 0)
	{
		Position* positionComponent = positionManager->getComponent(this->playerMovement->getEntity());
		Sprite* spriteComponent = spriteManager->getComponent(this->playerMovement->getEntity());
		Animator* animatorComponent = animatorManager->getComponent(this->playerMovement->getEntity());
		
		if (animatorComponent->getState() < STATES::ATK_SIDE && inputManager->getDirectionMagnitude() > 0.0) {
			// moving
			float newX = (inputManager->getNormalizedDirectionX() * this->playerMovement->getMovementSpeed());
			float newY = (inputManager->getNormalizedDirectionY() * this->playerMovement->getMovementSpeed());
			positionComponent->movePosition(newX, newY);
		}

		controlAnimationStates(this->playerMovement->getEntity(), inputManager->getDirection(), true);
	}
}

/**
* @brief Controls the animations of an entity.
* @param e - Entity to control animation states off.
* @param direction - Direction of movement if present.
* @param checkMouseInput - Whether mouse input should be checked.
*/
void PhysicSystem::controlAnimationStates(Entity e, Vector2* direction, bool checkMouseInput) {
	Sprite* spriteComponent = spriteManager->getComponent(e);
	Animator* animatorComponent = animatorManager->getComponent(e);
	Animation* currentAnimation = animatorComponent->getCurrentAnimation();

	// check if sprite component and animator are present
	if (animatorComponent != nullptr && spriteComponent != nullptr) {
		// get current state
		size_t state = animatorComponent->getState();

		if (!currentAnimation->interruptible) {
			if (currentAnimation->isFinished()) {

				// reset current animation
				currentAnimation->resetAnimation();

				switch (state) {
				case STATES::ATK_DOWN:
					animatorComponent->setState(STATES::IDLE_DOWN);
					break;
				case STATES::ATK_UP:
					animatorComponent->setState(STATES::IDLE_UP);
					break;
				case STATES::ATK_SIDE:
					animatorComponent->setState(STATES::IDLE_SIDE);
					break;
				default:
					animatorComponent->setState(STATES::IDLE_SIDE);
					break;
				}
			}
		}
		else if (checkMouseInput && inputManager->getMouseButton() == SDL_BUTTON_LEFT) {
			// TODO: have attack colliders 
			// attack
			switch (state) {
				case STATES::WALK_DOWN:
					animatorComponent->setState(STATES::ATK_DOWN);
					break;
				case STATES::WALK_UP:
					animatorComponent->setState(STATES::ATK_UP);
					break;
				case STATES::WALK_SIDE:
					animatorComponent->setState(STATES::ATK_SIDE);
					break;
				case STATES::IDLE_DOWN:
					animatorComponent->setState(STATES::ATK_DOWN);
					break;
				case STATES::IDLE_UP:
					animatorComponent->setState(STATES::ATK_UP);
					break;
				case STATES::IDLE_SIDE:
					animatorComponent->setState(STATES::ATK_SIDE);
					break;
				default:
					animatorComponent->setState(STATES::ATK_SIDE);
					break;
			}
		} 
		else if (direction->getMagnitude() > 0.0) {
			// moving
			if (direction->x > 0) {
				spriteComponent->setTextureFlip(SDL_FLIP_HORIZONTAL);
				animatorComponent->setState(STATES::WALK_SIDE);
			}
			else if (direction->x < 0) {
				spriteComponent->setTextureFlip(SDL_FLIP_NONE);
				animatorComponent->setState(STATES::WALK_SIDE);
			}
			else {
				if (direction->y > 0) {
					animatorComponent->setState(STATES::WALK_DOWN);
				}
				else {
					animatorComponent->setState(STATES::WALK_UP);
				}
			}
		}
		else if(direction->getMagnitude() == 0.0){
			// transition to idle
			switch (state) {
				case STATES::WALK_DOWN:
					animatorComponent->setState(STATES::IDLE_DOWN);
					break;
				case STATES::WALK_UP:
					animatorComponent->setState(STATES::IDLE_UP);
					break;
				case STATES::WALK_SIDE:
					animatorComponent->setState(STATES::IDLE_SIDE);
					break;
				default:
					//animatorComponent->setState(STATES::IDLE_SIDE);
					break;
			}
		}
	}
}

/**
* @brief Handles the movement of projectiles.
*/
void PhysicSystem::handleProjectileMovement() {
	size_t componentCount = this->projManager->getComponentCount();

	for (size_t i = 0; i < componentCount; i++)
	{
		ProjectileMovement* currentComponent = this->projManager->getComponentWithIndex(i);
		if (currentComponent->isActive()) {
			Position* positionComponent = this->positionManager->getComponent(currentComponent->getEntity());

			// moving
			float newX = (std::cos(currentComponent->getAngle() * M_PI / 180) * currentComponent->getProjectileSpeed());
			float newY = (std::sin(currentComponent->getAngle() * M_PI / 180) * currentComponent->getProjectileSpeed());
			positionComponent->movePosition(newX, newY);
		}
	}
}
/**
* @brief Handles the movement of enemies.
*/
void PhysicSystem::handleEnemyMovement() {
	size_t componentCount = this->enemyMovementManager->getComponentCount();
	Uint32 newTimestamp = SDL_GetTicks();

	for (size_t i = 0; i < componentCount; i++)
	{
		EnemyMovement* currentComponent = this->enemyMovementManager->getComponentWithIndex(i);
		Vector2 direction = { 0,0 };
		if (currentComponent->isActive() && currentComponent->getDestination() != nullptr) {
			Position* currPos = this->positionManager->getComponent(currentComponent->getEntity());

			// calculate path
			if (currentComponent->isFlagged()) {
				currentComponent->flag(false);
				Node* curr = this->getCurrentNode(currPos);
				currentComponent->setRoute(this->aStar(curr, currentComponent->getDestination()));
			}
			//move
			if (currentComponent->arrivedAtNextNode(currPos->x() / 32, currPos->y() / 32)) {
				currentComponent->setNextNode();
			}
			Node* currentTarget = currentComponent->getNextNode();
			direction.x = (currentTarget->x*tileWidth + tileWidth/2) - currPos->x();
			direction.y = (currentTarget->y*tileHeight + tileHeight/2) - currPos->y();

			// normalize direction
			float newX = direction.getNormalizedX();
			float newY = direction.getNormalizedY();

			currPos->movePosition(newX * currentComponent->getMovementSpeed(), newY * currentComponent->getMovementSpeed());

			// increase component timer
			currentComponent->increaseTimer(newTimestamp- lastEnemyMovementTimestamp);
		}
		// control animation state
		this->controlAnimationStates(currentComponent->getEntity(), &direction, false);
	}
	lastEnemyMovementTimestamp = newTimestamp;
}

/**
* @brief Handles collision between entities.
*/
void PhysicSystem::handleCollision(){
	//TODO: handle collision between objects and enemies.
	calculateColliderPositions();
	detectCollisions();
}

/**
 * @brief Calculates the positions of the colliders.
*/
void PhysicSystem::calculateColliderPositions(){
	size_t componentCount = colliderManager->getComponentCount();

	for (size_t i = 0; i < componentCount; i++) {
		Collider* currentCollider = colliderManager->getComponentWithIndex(i);

		if (this->playerMovement->getEntity().uid == currentCollider->getEntity().uid 
			||this->projManager->hasComponent(currentCollider->getEntity()) || this->enemyMovementManager->hasComponent(currentCollider->getEntity())) {
			// collider on moving player object
			Position* currentPosition = positionManager->getComponent(currentCollider->getEntity());
			adjustColliderPosition(currentCollider, currentPosition);
		}
	}
}

/**
* @brief Adjusts the position of the collider based on the position.
*/
void PhysicSystem::adjustColliderPosition(Collider* collider, Position* position) {
	SDL_Point* colliderOffset = collider->getColliderOffset();
	SDL_Point* colliderSize = collider->getColliderSize();

	int newX = (position->x() - (colliderSize->x / 2)) + colliderOffset->x;
	int newY = (position->y() - (colliderSize->y / 2)) + colliderOffset->y;

	collider->setColliderRect(newX, newY);
}

/**
* @brief Detects collisions between colliders.
*/
void PhysicSystem::detectCollisions() {
	size_t colliderCount = colliderManager->getComponentCount();
	size_t projectileMovementCount = projManager->getComponentCount();

	if(playerMovement != nullptr) {
		size_t collisionCounter = 0;

		Position* currentPosition = positionManager->getComponent(this->playerMovement->getEntity());
		Collider* currentCollider = colliderManager->getComponent(this->playerMovement->getEntity());

		if (currentCollider == nullptr) {
			return;
		}

		if (currentCollider->isActive()) {
			for (size_t z = 0; z < colliderCount; z++)
			{
				Collider* nextCollider = colliderManager->getComponentWithIndex(z);

				if (nextCollider->isActive()) {
					// check if both entities
					if (nextCollider->getEntity().uid != this->playerMovement->getEntity().uid) {
						if (SDL_HasIntersection(currentCollider->getColliderRect(), nextCollider->getColliderRect()) == SDL_TRUE) {
							// collision
							collisionCounter++;
							// execute collider collision behaviour
							if (nextCollider->isTrigger()) {
								nextCollider->collision(currentCollider);
							}
							else if (currentCollider->isTrigger()) {
								currentCollider->collision(nextCollider);
							}
							else {
								currentCollider->collision(nextCollider);
								nextCollider->collision(currentCollider);

								// adjust position
								currentPosition->restoreLastPosition();
								adjustColliderPosition(currentCollider, currentPosition);
							}
						}
					}
				}
			}
		}

		// if current collider does not collide with another collider, reset lastCollision
		if (collisionCounter == 0 && !currentCollider->getLastCollision().uid == 0) {
			Collider* lastCollider = colliderManager->getComponent(currentCollider->getLastCollision());
			if (lastCollider->getLastCollision().uid == currentCollider->getEntity().uid) {
				// check if last collision was with current entity. if this is the case, reset last collision.
				lastCollider->resetLastCollision();
			}
			currentCollider->resetLastCollision();
		}
	}
	
	for (size_t i = 0; i < projectileMovementCount; i++)
	{
		size_t collisionCounter = 0;
		ProjectileMovement* projMovement = this->projManager->getComponentWithIndex(i);

		if (!projMovement->isActive()) {
			continue;
		}
		Position* currentPosition = positionManager->getComponent(projMovement->getEntity());
		Collider* currentCollider = colliderManager->getComponent(projMovement->getEntity());

		if (currentCollider == nullptr) {
			return;
		}

		if (currentCollider->isActive()) {
			for (size_t z = 0; z < colliderCount; z++)
			{
				Collider* nextCollider = colliderManager->getComponentWithIndex(z);

				if (nextCollider->isActive()) {
					// check if both entities
					if (nextCollider->getEntity().uid != this->projManager->getComponentWithIndex(i)->getEntity().uid) {
						if (SDL_HasIntersection(currentCollider->getColliderRect(), nextCollider->getColliderRect()) == SDL_TRUE) {
							// collision
							collisionCounter++;

							// execute collider collision behaviour
							currentCollider->collision(nextCollider);
							break;
						}
					}
				}
			}
		}

		// if current collider does not collide with another collider, reset lastCollision
		if (collisionCounter == 0 && !currentCollider->getLastCollision().uid == 0) {
			Collider* lastCollider = colliderManager->getComponent(currentCollider->getLastCollision());
			if (lastCollider->getLastCollision().uid == currentCollider->getEntity().uid) {
				// check if last collision was with current entity. if this is the case, reset last collision.
				lastCollider->resetLastCollision();
			}
			currentCollider->resetLastCollision();
		}
	}
}

#pragma region AStar
/**
* @brief Calculates the heuristic cost of the position to the destination.
* @param pos - Position to calculate the heuristic cost of.
* @param dest - Destination node.
* @return Heuristic cost from the position to the destination.
*/
float PhysicSystem::calculateHCost(Node* pos, Node* dest) {
	float hCost = std::sqrt((pos->x-dest->x) * (pos->x - dest->x) + (pos->y - dest->y) * (pos->y - dest->y));
	return hCost;
}

/**
* @brief Calculates the path from the start node to the destination node using the a* algorithm.
* @param start - Startnode.
* @param dest - Destinationnode.
* @return Path from the start node to the destination node.
*/
std::vector<Node*> PhysicSystem::aStar(Node* start, Node* dest) {
	// TODO: handle multiple enemy pathings
	// reset nodes
	for (size_t x = 0; x < row; x++)
	{
		for (size_t y = 0; y < col; y++)
		{
			nodes[y * row + x].visited = false;
			nodes[y * row + x].fcost = INFINITY;
			nodes[y * row + x].gcost = INFINITY;
			nodes[y * row + x].parent = nullptr;
			nodes[y * row + x].obstacle = false;
		}
	}

	this->markNodesAsObstacles();

	Node* current = start;
	start->gcost = 0.0f;
	start->fcost = calculateHCost(start, dest);

	// nodes to test
	std::list<Node*> openNodes;
	openNodes.push_back(start);

	while (!openNodes.empty() && current != dest) {
		openNodes.sort([](const Node* l, const Node* r) {return l->fcost < r->fcost;});

		// remove visited nodes
		while (!openNodes.empty() && openNodes.front()->visited) {
			openNodes.pop_front();
		}

		if (openNodes.empty()) {
			break;
		}

		current = openNodes.front();
		current->visited = true;

		// check neighbours
		for (auto neighbour : current->neighbours) {
			if (!neighbour->obstacle || neighbour == dest) {
				if (!neighbour->visited) {
					openNodes.push_back(neighbour);
				}

				float gCostNeighbour = current->gcost + calculateHCost(current, neighbour);

				if (gCostNeighbour < neighbour->gcost) {
					neighbour->parent = current;
					neighbour->gcost = gCostNeighbour;

					neighbour->fcost = neighbour->fcost + calculateHCost(neighbour, dest);
				}
			}
		}
	}

	// backtrack found path
	std::vector<Node*> result;
	result.push_back(current);
	while (current->parent != nullptr) {
		current = current->parent;
		result.push_back(current);
	}

	return result;
}

/**
* @brief Gets the current Node based on the position.
* @param pos - Position to get the current node off.
* @return Current Node.
*/
Node* PhysicSystem::getCurrentNode(Position* pos) {
	int newX = pos->x() / tileWidth;
	int newY = pos->y() / tileHeight;

	int idx = newY * tilesPerRow + newX;

	if (idx < this->nodeCount) {
		return &this->nodes[idx];
	}
	return nullptr;
}

/**
* @brief Gets the current Node based on the position.
* @param pos - Position to get the current node off.
* @return Current Node.
*/
Node* PhysicSystem::getCurrentNode(SDL_Point pos) {
	int newX = pos.x / tileWidth;
	int newY = pos.y / tileHeight;

	int idx = newY * tilesPerRow + newX;

	if (idx < this->nodeCount) {
		return &this->nodes[idx];
	}
	return nullptr;
}

/**
* @brief Marks nodes as obstacle when the match the collider positions.
*/
void PhysicSystem::markNodesAsObstacles() {
	size_t componentCount = colliderManager->getComponentCount();

	for (size_t i = 0; i < componentCount; i++)
	{
		Collider* collider = colliderManager->getComponentWithIndex(i);

		if (collider->isActive() && !collider->isTrigger()) {
			Position* pos = positionManager->getComponent(collider->getEntity());

			SDL_Point* size = collider->getColliderSize();
			
			int colX = size->x / tileWidth;
			int colY = size->y / tileHeight;

			SDL_Point position = { pos->x() - (size->x / 2),  pos->y() - (size->y / 2) };
			Node* colNode = nullptr;

			if (colX > 0 && colY > 0) {
				// collider bigger or equal to a tile
				for (int x = 0; x < colX; x++)
				{
					for (int y = 0; y < colY; y++)
					{
						colNode = this->getCurrentNode({ position.x + x * tileWidth, position.y + y * tileHeight });
						if (colNode != nullptr) {
							colNode->obstacle = true;
						}
					}
				}
			}
			else if (colX > 0) {
				// collider height smaller than a tile
				for (int x = 0; x < colX; x++)
				{
					colNode = this->getCurrentNode({ position.x + x * tileWidth, position.y});
					if (colNode != nullptr) {
						colNode->obstacle = true;
					}
				}
			}
			else if (colY > 0) {
				// collider width smaller than a tile
				for (int y = 0; y < colY; y++)
				{
					colNode = this->getCurrentNode({ position.x, position.y + y * tileHeight });
					if (colNode != nullptr) {
						colNode->obstacle = true;
					}
				}
			}
			else {
				// collider smaller than a tile
				colNode = this->getCurrentNode({ position.x, position.y });
				if (colNode != nullptr) {
					colNode->obstacle = true;
				}
			}
		}
	}
}
#pragma endregion AStar