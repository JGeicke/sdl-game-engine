#pragma once
#include <iostream>
struct Scene {
	// function pointer
	typedef void (*sceneInitFunction)();
public:

	Scene(const char* tilesetPath, const char* tilemapDataPath, size_t layerCount, const char* bgmPath, sceneInitFunction initFunc) 
		: tilesetFilePath{tilesetPath}, tilemapDataFilePath{tilemapDataPath}, layerCount{layerCount}, bgmFilePath{bgmPath}, sceneInit{initFunc}
	{

	}

	void init() {
		if (this->sceneInit == nullptr) {
			std::cout << "Scene could not be initialized" << std::endl;
			return;
		}
		sceneInit();
	}

	const char* getTilesetFilePath() { return tilesetFilePath; }
	const char* getTilemapDataFilePath() { return tilemapDataFilePath; }
	size_t getLayerCount() { return layerCount; }
	const char* getBGMFilePath() { return bgmFilePath; }
private:
	const char* tilesetFilePath; 
	const char* tilemapDataFilePath; 
	size_t layerCount; 
	const char* bgmFilePath;
	sceneInitFunction sceneInit;
};