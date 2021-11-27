#pragma once
#include "SDL.h"
#include "../fileloader.h"
struct ProgressBar {
public:
	ProgressBar() {
		progressTexture = nullptr;
		bgTexture = nullptr;
		bgPosition = {};
		progressPosition = {};
		progress = 0.0f;
	}

	ProgressBar(SDL_Renderer* renderer, const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
		setPosition(x, y);
		setSize(w, h);
		bgTexture = FileLoader::loadSDLTexture(bgFilePath, renderer);
		progressTexture = FileLoader::loadSDLTexture(progressFilePath, renderer);
		colorTexture(bgTexture, bgColor);
		colorTexture(progressTexture, progressColor);
	}

	ProgressBar(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
		setPosition(x, y);
		setSize(w, h);
		bgTexture = FileLoader::loadSDLTexture("assets/base_panel.png", renderer);
		progressTexture = FileLoader::loadSDLTexture("assets/base_panel.png", renderer);
		colorTexture(bgTexture, bgColor);
		colorTexture(progressTexture, progressColor);
	}

	void setPosition(int x, int y) {
		bgPosition.x = x;
		bgPosition.y = y;

		progressPosition.x = x;
		progressPosition.y = y;
	}

	void setSize(int w, int h) {
		bgPosition.w = w;
		bgPosition.h = h;

		progressPosition.h = h;
	}

	void setProgress(float progress) {
		this->progress = progress;
		this->progressPosition.w = this->bgPosition.w * progress;
	}

	void setBackgroundColor(SDL_Color color) {
		colorTexture(bgTexture, color);
	}

	void setProgressColor(SDL_Color color) {
		colorTexture(progressTexture, color);
	}

	SDL_Texture* getBackgroundTexture() {
		return bgTexture;
	}

	SDL_Rect* getBackgroundPosition() {
		return &bgPosition;
	}

	SDL_Texture* getProgressTexture() {
		return progressTexture;
	}

	SDL_Rect* getProgressPosition() {
		return &progressPosition;
	}

	bool isVisible() {
		return visible;
	}

	void show(bool showPanel) {
		visible = showPanel;
	}
private:
	void colorTexture(SDL_Texture* texture, SDL_Color color) {
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	}

	SDL_Texture* progressTexture;
	SDL_Texture* bgTexture;
	SDL_Rect bgPosition;
	SDL_Rect progressPosition;

	float progress;

	bool visible = true;
};