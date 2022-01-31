#pragma once
#include <iostream>

/**
 * @brief Struct representing a game scene.
*/
struct Scene {
	// function pointer
	typedef void (*sceneInitFunction)();
public:

	/**
	 * @brief Creates new scene object.
	 * @param tilesetPath - File path to the tileset of the scene.
	 * @param tilemapDataPath - File path to the tilemap data of the scene.
	 * @param layerCount - Number of layers in the tilemap.
	 * @param bgmPath - File path to the background music of the scene.
	 * @param initFunc - Initialization function of the scene.
	*/
	Scene(const char* tilesetPath, const char* tilemapDataPath, size_t layerCount, const char* bgmPath, sceneInitFunction initFunc) 
		: tilesetFilePath{tilesetPath}, tilemapDataFilePath{tilemapDataPath}, layerCount{layerCount}, bgmFilePath{bgmPath}, sceneInit{initFunc}
	{

	}

	/**
	 * @brief Initializes the scene by calling the initialization function of the scene if present.
	*/
	void init() {
		if (this->sceneInit == nullptr) {
			std::cout << "Scene could not be initialized" << std::endl;
			return;
		}
		sceneInit();
	}

	/**
	 * @brief Gets the file path to the tileset.
	 * @return The file path to the tileset.
	*/
	const char* getTilesetFilePath() { return tilesetFilePath; }

	/**
	 * @brief Gets the file path to the tilemap data.
	 * @return The file path to the tilemap data.
	*/
	const char* getTilemapDataFilePath() { return tilemapDataFilePath; }

	/**
	 * @brief Gets the number of layers in the tilemap of the scene.
	 * @return Number of layers.
	*/
	size_t getLayerCount() { return layerCount; }

	/**
	 * @brief Gets the file path to the background music.
	 * @return The file path to the background music.
	*/
	const char* getBGMFilePath() { return bgmFilePath; }
private:
	/**
	 * @brief File path to the tileset.
	*/
	const char* tilesetFilePath; 
	/**
	 * @brief File path to the tilemap data.
	*/
	const char* tilemapDataFilePath; 
	/**
	 * @brief Number of layers in the tilemap.
	*/
	size_t layerCount; 
	/**
	 * @brief File path to the background music.
	*/
	const char* bgmFilePath;
	/**
	 * @brief Function pointer to the initialization function of the scene.
	*/
	sceneInitFunction sceneInit;
};