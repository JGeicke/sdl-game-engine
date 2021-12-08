#pragma once
#include <map>
#include <vector>
#include "SDL.h"
#include "../util/texture.h"
#include <iostream>
/**
 * @brief Struct to store all data for the tilemap.
*/
struct Tilemap {
public:
	/**
	 * @brief Creates new tilemap.
	 * @param tileWidth - Width of the tiles.
	 * @param tileHeight - Height of the tiles.
	 * @param tilesPerRow - Width of the tilemap / maximum tiles per row.
	 * @param tilesPerCol - Height of the tilemap / maximum tiles per column.
	*/
	Tilemap(unsigned int tileWidth, unsigned int tileHeight, unsigned int tilesPerRow, unsigned int tilesPerCol) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->tilesPerCol = tilesPerCol;
		this->tilesPerRow = tilesPerRow;
		layerCount = 0;
	}

	/**
	 * @brief Adds a layer to the tilemap.
	 * @param layer - Index of layer to add.
	 * @param vector - Layer data stored in an vector.
	*/
	void addLayer(size_t layer, std::vector<unsigned int> vector) {
		layers.insert(std::pair<size_t, std::vector<unsigned int>>(layer, vector));
		layerCount++;
	}

	/**
	 * @brief Adds an object to the object layer.
	 * @param obj - Object to add.
	*/
	void addObject(SDL_Rect obj) {
		objectLayer.insert(objectLayer.begin() + objectIndex, obj);
		objectIndex++;
		std::cout << obj.x << " " << obj.y << " " << obj.w << " " << obj.h << std::endl;
	}

	/**
	 * @brief Prints layer with certain index.
	 * @param layer - Index of layer to print.
	*/
	void print(size_t layer) {
		std::vector<unsigned int> vec = layers[layer];
		for (size_t i = 0; i < vec.size(); i++)
		{
			std::cout << vec[i] << std::endl;
		}
	}

	/**
	 * @brief Gets the tilemap data of layer with certain index.
	 * @param layer - Index of layer to get the data from
	 * @return Data of tilemap layer. Returns nullptr if given layer index is not allowed.
	*/
	std::vector<unsigned int> getLayer(size_t layer) {
		if (layer < layerCount) {
			return layers[layer];
		}
		return std::vector<unsigned int>();
	}

	/**
	 * @brief Gets the object layer of the tilemap.
	 * @return Object layer of the tilemap.
	*/
	std::vector<SDL_Rect> getObjectLayer() {
		return objectLayer;
	}

	/**
	 * @brief Gets current layer count of tilemap.
	 * @return Current layer count of tilemap.
	*/
	size_t getLayerCount() {
		return layerCount;
	}

	/**
	 * @brief Gets tile width of the tilemap.
	 * @return Tile width of the tilemap.
	*/
	unsigned int getTileWidth() {
		return tileWidth;
	}

	/**
	 * @brief Gets tile height of the tilemap.
	 * @return Tile height of the tilemap.
	*/
	unsigned int getTileHeight() {
		return tileHeight;
	}

	/**
	 * @brief Gets maximum tile count per row of the tilemap.
	 * @return Map width (or maximum tiles per row) of the tilemap.
	*/
	unsigned int getTilesPerRow() {
		return tilesPerRow;
	}

	/**
	 * @brief Gets maximum tile count per column of the tilemap.
	 * @return Map height (or maximum tiles per column) of the tilemap.
	*/
	unsigned int getTilesPerCol() {
		return tilesPerCol;
	}

	/**
	 * @brief Gets total width of the tilemap.
	 * @return Total width of the tilemap.
	*/
	unsigned int getTotalTilemapWidth() {
		return tilesPerRow * tileWidth;
	}

	/**
	 * @brief Gets total height of the tilemap.
	 * @return Total height of the tilemap.
	*/
	unsigned int getTotalTilemapHeight() {
		return tilesPerCol * tileHeight;
	}

	/**
	 * @brief Gets the collision layer index of the tilemap.
	 * @return The collision layer index.
	*/
	int getCollisionLayerIndex() {
		return collisionLayerIndex;
	}

	/**
	 * @brief Sets the current collision layer index.
	 * @param index - New collision layer index.
	*/
	void setCollisionLayerIndex(int index) {
		if (hasCollisionLayer()) {
			std::cout << "Multiple collision layers!" << std::endl;
		}
		collisionLayerIndex = index;
	}

	/**
	 * @brief Checks if tilemap has collision layer.
	 * @return Whether the tilemap has a collision layer.
	*/
	bool hasCollisionLayer() {
		return collisionLayerIndex != -1;
	}
private:
	/**
	 * @brief Width of each tile in the tilemap.
	*/
	unsigned int tileWidth;

	/**
	 * @brief Height of each tile in the tilemap.
	*/
	unsigned int tileHeight;

	/**
	 * @brief Maximum tiles per row in tilemap.
	*/
	unsigned int tilesPerRow;

	/**
	 * @brief Maximum tiles per column in tilemap.
	*/
	unsigned int tilesPerCol;
	
	/**
	 * @brief Current count of layers in the tilemap.
	*/
	size_t layerCount;

	/**
	 * @brief Data of each tile layer stored in a map with layer index as the key.
	*/
	std::map<size_t, std::vector<unsigned int> > layers = {};

	/**
	 * @brief Data of each object layer stored in a map with layer index as the key.
	*/
	std::vector<SDL_Rect> objectLayer = {};

	/**
	 * @brief Current object count of object layer.
	*/
	size_t objectIndex = 0;

	/**
	 * @brief Current collision layer index.
	*/
	int collisionLayerIndex = -1;

};

/**
 * @brief Struct to store data of the tileset used to display the tilemap.
*/
struct Tileset {
public:
	/**
	 * @brief Creates new tileset.
	 * @param tilesetTexture - Reference to the tileset texture.
	*/
	Tileset(Texture tilesetTexture) {
		this->tilesetTexture = tilesetTexture;
		this->tilesetDestinationRect = {};
		this->tilesetSourceRect = {};
	}

	/**
	 * @brief Initializes source rectangle of the tileset with tile width and tile height.
	 * @param width - Width of each tile in tileset.
	 * @param height - Height of each tile in tileset.
	*/
	void initSourceRect(unsigned int width, unsigned int height) {
		tilesetSourceRect.w = width;
		tilesetSourceRect.h = height;
	}

	/**
	 * @brief Initializes destination rectangle of the tileset with tile width and tile height.
	 * @param width - Width of each tile in tileset.
	 * @param height - Height of each tile in tileset.
	*/
	void initDestinationRect(unsigned int width, unsigned int height) {
		tilesetDestinationRect.w = width;
		tilesetDestinationRect.h = height;
	}

	/**
	 * @brief Sets the x/y position of the source rectangle. Determines which tile will be displayed of the tileset.
	 * @param x - X position of the source rectangle.
	 * @param y - Y position of the source rectangle.
	*/
	void setSourceRect(unsigned int x, unsigned int y) {
		tilesetSourceRect.x = x;
		tilesetSourceRect.y = y;
	}

	/**
	 * @brief Sets the x/y position of the destination rectangle. Determines where in the game window the tile will be displayed.
	 * @param x - X position of the destination rectangle.
	 * @param y - Y position of the destination rectangle.
	*/
	void setDestinationRect(unsigned int x, unsigned int y) {
		tilesetDestinationRect.x = x;
		tilesetDestinationRect.y = y;
	}

	/**
	 * @brief Gets the texture of the tileset.
	 * @return Texture of the tileset.
	*/
	Texture getTexture() {
		return tilesetTexture;
	}

	/**
	 * @brief Gets the source rectangle of the tileset texture.
	 * @return Source rectangle of the tileset texture.
	*/
	SDL_Rect* getSourceRect() {
		return &tilesetSourceRect;
	}

	/**
	 * @brief Gets the destination rectangle of the tileset texture.
	 * @return Destination rectangle of the tileset texture.
	*/
	SDL_Rect* getDestinationRect() {
		return &tilesetDestinationRect;
	}
private:
	/**
	 * @brief Tileset texture.
	*/
	Texture tilesetTexture;

	/**
	 * @brief The source rectangle of the tileset texture. Determins which part of the tileset will be displayed.
	*/
	SDL_Rect tilesetSourceRect;

	/**
	 * @brief The destination rectangle of the tileset texture. Determins where the part of the tileset will be displayed in the game window.
	*/
	SDL_Rect tilesetDestinationRect;
};