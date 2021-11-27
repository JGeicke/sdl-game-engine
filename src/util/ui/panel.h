#pragma once
#include "SDL.h"
#include "SDL_image.h"
struct Panel {
public:
	Panel() {
		panelTexture = nullptr;
		displayPosition = {0,0,0,0};
	}

	Panel(SDL_Renderer* renderer, const char* filePath, int x, int y, int w, int h) {
		setPosition(x, y);
		setSize(w, h);

		createPanelTexture(renderer, filePath);
	}

	Panel(SDL_Renderer* renderer, int x, int y, int w, int h) {
		setPosition(x, y);
		setSize(w, h);

		// use base panel texture
		createPanelTexture(renderer, "assets/base_panel.png");
	}

	void setPosition(int x, int y) {
		displayPosition.x = x;
		displayPosition.y = y;
	}

	void setSize(int w, int h) {
		displayPosition.w = w;
		displayPosition.h = h;
	}

	SDL_Texture* getPanelTexture() {
		return panelTexture;
	}

	SDL_Rect* getDisplayPosition() {
		return &displayPosition;
	}
private:
	SDL_Texture* panelTexture;
	SDL_Rect displayPosition;

	void createPanelTexture(SDL_Renderer* renderer, const char* filePath) {
		SDL_Surface* tempSurface = IMG_Load(filePath);
		this->panelTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}
};