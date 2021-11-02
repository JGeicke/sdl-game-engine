#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

/**
 * @brief Abstract base class of game systems.
*/
class GameSystem {
	/**
	 * @brief Virtual function that initializes the game system.
	*/
	virtual void init(){}

	/**
	 * @brief Update loop of every game system.
	*/
	virtual void update() = 0;
};
#endif // !GAMESYSTEM_H

