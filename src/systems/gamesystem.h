#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

/**
 * @brief Abstract base class of game systems.
*/
class GameSystem {
public:
	/**
	 * @brief Virtual function that initializes the game system.
	*/
	virtual void init(){}

	/**
	 * @brief Update loop of every game system.
	*/
	virtual void update() = 0;

	/**
	 * @brief Enables/disables debug mode for game system.
	 * @param startDebug - 
	*/
	void debugging(bool startDebug) {
		debug = startDebug;
	}
protected:
	/**
	 * @brief Whether the gamesystem runs in debug mode.
	*/
	bool debug = false;
};
#endif // !GAMESYSTEM_H

