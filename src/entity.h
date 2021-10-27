#ifndef ENTITY_H
#define ENTITY_H
/**
 * @brief Base struct to represent Entities in the game.
*/
struct Entity {
	/**
	 * @brief unique identifier for each entity.
	*/
	unsigned int uid;

	bool operator== (const Entity& other) const {
		return uid == other.uid;
	}
};
#endif
