#include "fileloader.h"
/**
* @brief Loads, parses and creates the tilemap from tilemap json files created with tiled.
* @param path - File path to json file.
* @param layerCount - Layer count of the tilemap.
* @return Created tilemap.
*/
Tilemap* FileLoader::loadTilemap(const char* path, size_t layerCount) {
	std::ifstream file;
	std::string s;
	file.open(path);

	if (file.is_open()) {
		// first argument creates iterator at the beginning of the ifstream, second argument is the default constructor which represents the end of the stream.
		std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		json tilemap_raw = json::parse(content);

		Tilemap* result = new Tilemap(tilemap_raw["tilewidth"], tilemap_raw["tileheight"], tilemap_raw["width"], tilemap_raw["height"]);

		for (size_t i = 0; i < layerCount; i++)
		{
			// add layer
			result->addLayer(i, tilemap_raw["layers"][i]["data"].get<std::vector<unsigned int>>());
		}
		file.close();
		return result;
	}
	return NULL;
}

