#pragma once
#include <map>
#include <vector>
#include "SDL.h"
struct Tilemap {
public:
	Tilemap(unsigned int tileWidth, unsigned int tileHeight, unsigned int mapWidth, unsigned int mapHeight) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->mapHeight = mapHeight;
		this->mapWidth = mapWidth;
		layerCount = 0;
	}

	void addLayer(size_t layer, std::vector<unsigned int> vector) {
		layers.insert(std::pair<size_t, std::vector<unsigned int>>(layer, vector));
		layerCount++;
	}

	void print(size_t layer) {
		std::vector<unsigned int> vec = layers[layer];
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << std::endl;
		}
	}

	std::vector<unsigned int> getLayer(size_t layer) {
		if (layer < layerCount) {
			return layers[layer];
		}
	}

	size_t getLayerCount() {
		return layerCount;
	}

	unsigned int getTileWidth() {
		return tileWidth;
	}
	unsigned int getTileHeight() {
		return tileHeight;
	}

	unsigned int getMapWidth() {
		return mapWidth;
	}
	unsigned int getMapHeight() {
		return mapHeight;
	}
private:
	unsigned int tileWidth;
	unsigned int tileHeight;

	unsigned int mapWidth;
	unsigned int mapHeight;
	
	size_t layerCount;
	std::map<size_t, std::vector<unsigned int> > layers = {};

};
struct Tileset {
public:
	Tileset(SDL_Texture* tilesetTexture, unsigned int tilesetWidth, unsigned int tilesetHeight) {
		this->tilesetTexture = tilesetTexture;
		this->tilesetWidth = tilesetWidth;
		this->tilesetHeight = tilesetHeight;
	}

	void initSourceRect(unsigned int width, unsigned int height) {
		tilesetSourceRect.w = width;
		tilesetSourceRect.h = height;
	}

	void initDestinationRect(unsigned int width, unsigned int height) {
		tilesetDestinationRect.w = width;
		tilesetDestinationRect.h = height;
	}

	void setSourceRect(unsigned int x, unsigned int y) {
		tilesetSourceRect.x = x;
		tilesetSourceRect.y = y;
	}

	void setDestinationRect(unsigned int x, unsigned int y) {
		tilesetDestinationRect.x = x;
		tilesetDestinationRect.y = y;
	}

	SDL_Texture* getTexture() {
		return tilesetTexture;
	}

	SDL_Rect* getSourceRect() {
		return &tilesetSourceRect;
	}

	SDL_Rect* getDestinationRect() {
		return &tilesetDestinationRect;
	}

	unsigned int getTilesetWidth() {
		return tilesetWidth;
	}
private:
	SDL_Texture* tilesetTexture;

	SDL_Rect tilesetSourceRect;

	SDL_Rect tilesetDestinationRect;

	unsigned int tilesetWidth;

	unsigned int tilesetHeight;
};