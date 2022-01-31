#pragma once
#include "SDL.h"
#include "../util/texture.h"
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
		this->init(texturePath, 0, 0, width, height, scale);
	}

	/**
	 * @brief Initializes the sprite component with custom source rectangle position.
	 * @param srcX - X position of source rectangle.
	 * @param srcY - Y position of source rectangle.
	 * @param texturePath - Filepath to the sprite image
	 * @param width - Width of the sprite image
	 * @param height - Height of the sprite image
	 * @param scale - Scales how the sprite image should be scaled ingame
	*/
	void init(const char* texturePath,int srcX, int srcY, int width, int height, float scale) {
		sourceRect.x = srcX;
		sourceRect.y = srcY;
		sourceRect.w = width;
		sourceRect.h = height;
		destinationRect.w = (int)(width * scale);
		destinationRect.h = (int)(height * scale);

		this->texturePath = texturePath;
		texture.texture = nullptr;

		currentTextureFlip = SDL_FLIP_NONE;
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
		return texture.texture;
	}

	/**
	 * @brief Set the texture of the sprite component.
	 * @param tex - New sprite texture.
	*/
	void setTexture(Texture t) {
		texture = t;
	}

	/**
	 * @brief Gets the texture of the sprite component.
	 * @return Texture of sprite component.
	*/
	Texture getTexture() {
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
	 * @brief Gets the current texture flip.
	 * @return The current texture flip.
	*/
	SDL_RendererFlip getTextureFlip() {
		return currentTextureFlip;
	}

	/**
	 * @brief Sets the current texture flip.
	 * @param textureFlip - New texture flip.
	*/
	void setTextureFlip(SDL_RendererFlip textureFlip) {
		currentTextureFlip = textureFlip;
	}
private:
	/**
	 * @brief Texture with SDL_Texture and the texture size.
	*/
	Texture texture;
	/**
	 * @brief Area of texture to display ingame.
	*/
	SDL_Rect sourceRect = { 0,0,0,0 };;
	/**
	 * @brief Area and size where the texture should be drawn on ingame.
	*/
	SDL_Rect destinationRect = { 0,0,0,0 };

	/**
	 * @brief Determines how the texture is currently flipped.
	*/
	SDL_RendererFlip currentTextureFlip;
};
