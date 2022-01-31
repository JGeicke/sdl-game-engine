#pragma once
#include "SDL.h"
/**
 * @brief Struct to store texture and texture data.
*/
struct Texture {
	/**
	 * @brief Initializes an empty struct.
	*/
	void emptyInit() {
		texture = nullptr;
		textureWidth = -1;
		textureHeight = -1;
	}

	/**
	 * @brief Pointer to the displayed texture.
	*/
	SDL_Texture* texture;
	/**
	 * @brief Width of the texture.
	*/
	int textureWidth;
	/**
	 * @brief Height of the texture.
	*/
	int textureHeight;
};