#pragma once
#include <map>
#include <vector>
#include "SDL.h"
/**
 * @brief Struct to store all data for the tilemap.
*/
struct Tilemap {
public:
	/**
	 * @brief Creates new tilemap.
	 * @param tileWidth - Width of the tiles.
	 * @param tileHeight - Height of the tiles.
	 * @param mapWidth - Width of the tilemap / maximum tiles per row.
	 * @param mapHeight - Height of the tilemap / maximum tiles per column.
	*/
	Tilemap(unsigned int tileWidth, unsigned int tileHeight, unsigned int mapWidth, unsigned int mapHeight) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->mapHeight = mapHeight;
		this->mapWidth = mapWidth;
		layerCount = 0;
	}

	/**
	 * @brief Adds a layer to the tilemap.
	 * @param layer - Index of layer to add.
	 * @param vector - Layer data stored in vector.
	*/
	void addLayer(size_t layer, std::vector<unsigned int> vector) {
		layers.insert(std::pair<size_t, std::vector<unsigned int>>(layer, vector));
		layerCount++;
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
	 * @return Data of tilemap layer.
	*/
	std::vector<unsigned int> getLayer(size_t layer) {
		if (layer < layerCount) {
			return layers[layer];
		}
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
	 * @brief Gets map width (or maximum tiles per row) of the tilemap.
	 * @return Map width (or maximum tiles per row) of the tilemap.
	*/
	unsigned int getMapWidth() {
		return mapWidth;
	}

	/**
	 * @brief Gets map height (or maximum tiles per column) of the tilemap.
	 * @return Map height (or maximum tiles per column) of the tilemap.
	*/
	unsigned int getMapHeight() {
		return mapHeight;
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
	 * @brief Map width (or maximum tiles per row) of tilemap.
	*/
	unsigned int mapWidth;

	/**
	 * @brief Map height (or maximum tiles per column) of tilemap.
	*/
	unsigned int mapHeight;
	
	/**
	 * @brief Current count of layers in the tilemap.
	*/
	size_t layerCount;

	/**
	 * @brief Data of each layer stored in a map with layer index as the key.
	*/
	std::map<size_t, std::vector<unsigned int> > layers = {};

};

/**
 * @brief Struct to store data of the tileset used to display the tilemap.
*/
struct Tileset {
public:
	/**
	 * @brief Creates new tileset.
	 * @param tilesetTexture - Reference to the tileset texture.
	 * @param tilesetWidth - Width of the tileset image.
	 * @param tilesetHeight - Height of the tileset image.
	*/
	Tileset(SDL_Texture* tilesetTexture, unsigned int tilesetWidth, unsigned int tilesetHeight) {
		this->tilesetTexture = tilesetTexture;
		this->tilesetWidth = tilesetWidth;
		this->tilesetHeight = tilesetHeight;
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
	SDL_Texture* getTexture() {
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

	/**
	 * @brief Gets the width of the tileset image.
	 * @return Width of the tileset image.
	*/
	unsigned int getTilesetWidth() {
		return tilesetWidth;
	}
private:
	/**
	 * @brief Reference to the tileset texture.
	*/
	SDL_Texture* tilesetTexture;

	/**
	 * @brief The source rectangle of the tileset texture. Determins which part of the tileset will be displayed.
	*/
	SDL_Rect tilesetSourceRect;

	/**
	 * @brief The destination rectangle of the tileset texture. Determins where the part of the tileset will be displayed in the game window.
	*/
	SDL_Rect tilesetDestinationRect;

	/**
	 * @brief Width of the tileset image (e.g. 512px).
	*/
	unsigned int tilesetWidth;

	/**
	 * @brief Height of the tileset image (e.g. 512px).
	*/
	unsigned int tilesetHeight;
};