#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "tilemap.h"
#include "SDL_image.h"
#include "texture.h"

//TODO: research how to handle includes in c++ git repos
#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

/**
 * @brief Utility class to handle file loading.
*/
class FileLoader {
public:
	/**
	 * @brief Loads, parses and creates the tilemap from tilemap json files created with tiled.
	 * @param path - File path to json file.
	 * @param layerCount - Layer count of the tilemap.
	 * @return Pointer to created tilemap.
	*/
	static Tilemap* loadTilemap(const char* path, size_t layerCount);

	/**
	 * @brief Loads texture from given path.
	 * @param path - File path to texture file.
	 * @param renderer - Reference to window renderer.
	 * @return Pointer to created texture.
	*/
	static Texture loadTexture(const char* path, SDL_Renderer* renderer);

	/**
	 * @brief Loads SDL_Texture from given path.
	 * @param path - File path to texture file.
	 * @param renderer - Reference to window renderer.
	 * @return Pointer to created SDL_Texture.
	*/
	static SDL_Texture* loadSDLTexture(const char* path, SDL_Renderer* renderer);
};