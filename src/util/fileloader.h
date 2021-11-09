#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "tilemap.h"

//TODO: research how to handle includes in c++ git repos
#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;
class FileLoader {
public:
	static Tilemap* loadTilemap(const char* path, size_t layerCount);
};