#ifndef ENTITY_H
#define ENTITY_H
/**
 * @brief Base struct to represent Entities in the game.
*/
struct Entity {
	/**
	 * @brief Unique identifier for each entity.
	*/
	unsigned int uid;

	/**
	 * @brief Overloading == operator to be able to check if entities are equal or not.
	 * @param other - Other entity to check if equal
	 * @return Whether both entities are equal or not
	*/
	bool operator== (const Entity& other) const {
		return uid == other.uid;
	}
};
#endif
