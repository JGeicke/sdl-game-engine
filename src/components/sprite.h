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
	void init(const char* texturePath, int width, int height, float scale) {
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = width;
		sourceRect.h = height;
		destinationRect.w = (int) (width * scale);
		destinationRect.h = (int) (height * scale);

		this->texturePath = texturePath;
		texture = nullptr;
	}

	/**
	 * @brief Prints the sprite component.
	*/
	void print() {
		std::cout << "Sprite (Entity: " << entity.uid << ") Path: " << texturePath << std::endl;
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
	 * @param tex - New sprite texture.
	 * @param textureWidth - Width of the texture.
	 * @param textureHeight - Height of the texture.
	*/
	void setTexture(SDL_Texture* tex, int textureWidth, int textureHeight) {
		texture = tex;
		this->textureWidth = textureWidth;
		this->textureHeight = textureHeight;
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

	/**
	 * @brief Gets destination rectangle width;
	 * @return Destination rectangle width
	*/
	unsigned int getDestinationWidth() {
		return destinationRect.w;
	}

	/**
	 * @brief Gets destination rectangle height;
	 * @return Destination rectangle height
	*/
	unsigned int getDestinationHeight() {
		return destinationRect.h;
	}

	/**
	 * @brief Gets source rectangle width;
	 * @return Source rectangle width
	*/
	unsigned int getSourceWidth() {
		return sourceRect.w;
	}

	/**
	 * @brief Gets source rectangle height;
	 * @return Source rectangle height
	*/
	unsigned int getSourceHeight() {
		return sourceRect.h;
	}

	/**
	 * @brief Sets the position of the source rectangle. Directily influences what part of the sprite will be displayed.
	 * @param x - X position of the sprite.
	 * @param y - Y position of the sprite
	*/
	void setSourceRectPosition(int x, int y) {
		sourceRect.x = x;
		sourceRect.y = y;
	}

	/**
	 * @brief Gets the source rectangle of the sprite component. The source rectangle is the area of the sprite which will be displayed.
	 * @return The source rectangle of the sprite component.
	*/
	SDL_Rect* getSourceRect() {
		return &sourceRect;
	}

	/**
	 * @brief Gets width of texture.
	 * @return Width of texture.
	*/
	int getTextureWidth() {
		return textureWidth;
	}

	/**
	 * @brief Gets height of texture.
	 * @return Height of texture.
	*/
	int getTextureHeight() {
		return textureHeight;
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

	/**
	 * @brief Width of texture.
	*/
	int textureWidth;

	/**
	 * @brief Height of texture.
	*/
	int textureHeight;
};
#endif // !SPRITE_H
