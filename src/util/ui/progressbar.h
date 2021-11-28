#pragma once
#include "SDL.h"
#include "../fileloader.h"
struct ProgressBar: UIElement {
public:
	ProgressBar() {
		progress = 0.0f;
	}

	ProgressBar(SDL_Renderer* renderer, const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
		progressPanel = *(new Panel(renderer, progressFilePath, x,y,w,h,progressColor));
		progressPanel.setPosition(x, y);
		backgroundPanel = *(new Panel(renderer, bgFilePath, x, y, w, h, bgColor));
		backgroundPanel.setPosition(x, y);

		progressPanel.setPanelColor(progressColor);
		backgroundPanel.setPanelColor(bgColor);

		progress = 0.0f;
	}

	ProgressBar(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
		progressPanel = *(new Panel(renderer, x, y, w, h, progressColor));
		progressPanel.setPosition(x, y);
		backgroundPanel = *(new Panel(renderer, x, y, w, h, bgColor));
		backgroundPanel.setPosition(x, y);

		progressPanel.setPanelColor(progressColor);
		backgroundPanel.setPanelColor(bgColor);

		progress = 0.0f;
	}

	void setPosition(int x, int y) {
		progressPanel.setPosition(x, y);
		backgroundPanel.setPosition(x, y);
	}

	void setSize(int w, int h) {
		backgroundPanel.setSize(w, h);
		progressPanel.setHeight(h);
	}

	void setProgress(float progress) {
		this->progress = progress;
		progressPanel.setWidth(backgroundPanel.getWidth() * progress);
	}

	void setBackgroundColor(SDL_Color color) {
		backgroundPanel.setPanelColor(color);
	}

	void setProgressColor(SDL_Color color) {
		progressPanel.setPanelColor(color);
	}

	SDL_Texture* getBackgroundTexture() {
		return backgroundPanel.getPanelTexture();
	}

	SDL_Rect* getBackgroundPosition() {
		return backgroundPanel.getDisplayPosition();
	}

	SDL_Texture* getProgressTexture() {
		return progressPanel.getPanelTexture();
	}

	SDL_Rect* getProgressPosition() {
		return progressPanel.getDisplayPosition();
	}
private:
	void colorTexture(SDL_Texture* texture, SDL_Color color) {
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	}

	Panel progressPanel;
	Panel backgroundPanel;

	float progress;
};