#ifndef SPRITE_H
#define SPRITE_H
#include "SDL.h"
struct Sprite : BaseComponent {
public:
	const char* texturePath = "";

	void init(const char* texturePath, int width, int height, int scale) {
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = width;
		sourceRect.h = height;
		destinationRect.w = width * scale;
		destinationRect.h = height * scale;

		this->texturePath = texturePath;
		texture = nullptr;
	}

	void print() {
		// TODO
	}

	bool hasTexture() {
		return texture != nullptr;
	}

	void setTexture(SDL_Texture* tex) {
		texture = tex;
	}

	SDL_Texture* getTexture() {
		return texture;
	}

	SDL_Rect* getDestinationRect() {
		return &destinationRect;
	}

	void setDestinationRectPosition(int x, int y) {
		destinationRect.x = x;
		destinationRect.y = y;
	}
private:
	SDL_Texture* texture;
	// part of texture to draw
	SDL_Rect sourceRect;
	// where to draw on screen
	SDL_Rect destinationRect;
};
#endif // !SPRITE_H
