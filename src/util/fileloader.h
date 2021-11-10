#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "tilemap.h"

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
	 * @return Created tilemap.
	*/
	static Tilemap* loadTilemap(const char* path, size_t layerCount);
};