#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "../fileloader.h"
struct Panel {
public:
	Panel() {
		panelTexture = nullptr;
		displayPosition = {0,0,0,0};
	}

	Panel(SDL_Renderer* renderer, const char* filePath, int x, int y, int w, int h, SDL_Color panelColor) {
		setPosition(x, y);
		setSize(w, h);

		this->panelTexture = FileLoader::loadSDLTexture(filePath, renderer);
		setPanelColor(panelColor);
	}

	Panel(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color panelColor) {
		setPosition(x, y);
		setSize(w, h);

		// use base panel texture
		this->panelTexture = FileLoader::loadSDLTexture("assets/base_panel.png", renderer);
		setPanelColor(panelColor);
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

	void setPanelColor(SDL_Color color) {
		SDL_SetTextureColorMod(panelTexture, color.r, color.g, color.b);
	}
private:
	SDL_Texture* panelTexture;
	SDL_Rect displayPosition;
};