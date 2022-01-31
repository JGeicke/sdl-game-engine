#pragma once
#include <cmath>
/**
 * @brief Structure to represent 2D position and vectors.
*/
struct Vector2 {
	/**
	 * @brief X-component of the vector.
	*/
	int x;
	/**
	 * @brief Y-component of the vector.
	*/
	int y;

	/**
	 * @brief Calculates magnitude of vector and returns it. Used by physic system for movement.
	 * @return Magnitude of vector.
	*/
	double getMagnitude() {
		return std::sqrt((x * x) + (y * y));
	}

	/**
	 * @brief Gets normalized x value of vector.
	 * @return Normalized x value.
	*/
	double getNormalizedX() {
		return x / getMagnitude();
	}

	/**
	 * @brief Gets normalized y value of vector.
	 * @return Normalized y value.
	*/
	double getNormalizedY() {
		return y / getMagnitude();
	}
};