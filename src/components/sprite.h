#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
/**
 * @brief Component to store sprites that visually represent the entities in the game world.
*/
struct Sprite : BaseComponent {
public:
	/**
	 * @brief Filepath to the sprite image file.
	*/
	const char* texturePath = "";

	/**
	 * @brief Initializes the sprite component.
	 * @param texturePath - Filepath to the sprite image
	 * @param width - Width of the sprite image
	 * @param height - Height of the sprite image
	 * @param scale - Scales how the sprite image should be scaled ingame
	*/
	void init(const char* texturePath, int width, int height, int scale) {
		// TODO: change scale from int to float
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = width;
		sourceRect.h = height;
		destinationRect.w = width * scale;
		destinationRect.h = height * scale;

		this->texturePath = texturePath;
		texture = nullptr;
	}

	/**
	 * @brief Printing the the sprite component.
	*/
	void print() {
		// TODO
	}

	/**
	 * @brief Check if sprite component has texture.
	 * @return Whether sprite component has texture.
	*/
	bool hasTexture() {
		return texture != nullptr;
	}

	/**
	 * @brief Set the texture of the sprite component.
	 * @param tex - New sprite texture
	*/
	void setTexture(SDL_Texture* tex) {
		texture = tex;
	}

	/**
	 * @brief Gets sprite texture of the sprite component.
	 * @return SDL_Texture of sprite component.
	*/
	SDL_Texture* getTexture() {
		return texture;
	}

	/**
	 * @brief Gets the destination rectangle of the sprite component. The destination rectangle is the area where the sprite will be displayed ingame.
	 * @return The destination rectangle of the sprite component.
	*/
	SDL_Rect* getDestinationRect() {
		return &destinationRect;
	}

	/**
	 * @brief Sets the position of the destination rectangle. Directily influences where the sprite will be displayed ingame.
	 * @param x - X position of the sprite.
	 * @param y - Y position of the sprite
	*/
	void setDestinationRectPosition(int x, int y) {
		destinationRect.x = x;
		destinationRect.y = y;
	}
private:
	/**
	 * @brief Created SDL_Texture of the given sprite file path.
	*/
	SDL_Texture* texture;
	/**
	 * @brief Area of texture to display ingame.
	*/
	SDL_Rect sourceRect;
	/**
	 * @brief Area and size where the texture should be drawn on ingame.
	*/
	SDL_Rect destinationRect;
};
#endif // !SPRITE_H
