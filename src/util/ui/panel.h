#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "../fileloader.h"
#include "uielement.h"
struct Panel: UIElement {
public:
	Panel() {
		panelTexture = nullptr;
		displayPosition = {0,0,0,0};
	}

	~Panel() {
		SDL_DestroyTexture(panelTexture);
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

	void setWidth(int w) {
		displayPosition.w = w;
	}

	void setHeight(int h) {
		displayPosition.h = h;
	}

	SDL_Texture* getPanelTexture() {
		return panelTexture;
	}

	SDL_Rect* getDisplayPosition() {
		return &displayPosition;
	}

	int getWidth() {
		return displayPosition.w;
	}

	void setPanelColor(SDL_Color color) {
		SDL_SetTextureColorMod(panelTexture, color.r, color.g, color.b);
	}
private:
	SDL_Texture* panelTexture;
	SDL_Rect displayPosition;
};