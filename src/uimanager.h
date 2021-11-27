#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "util/ui/label.h"

class UIManager {
public:
	UIManager(SDL_Renderer* renderer);
	void addFont(const char* path, int fontSize);

	size_t addLabel(int x, int y, std::string text, SDL_Color color, size_t fontIndex);
	Label* getLabel(size_t index) {
		if (index < currentLabelIndex) {
			return &uiLabels[index];
		}
	}
	void setLabelText(size_t labelIndex, std::string labelText);
	void setLabelPosition(size_t labelIndex, int x, int y);
	void setLabelTextColor(size_t labelIndex, SDL_Color textColor);
	size_t getCurrentLabelIndex() {
		return currentLabelIndex;
	}

private:
	SDL_Renderer* renderer;

	TTF_Font* fonts[3];
	size_t currentFontIndex;

	Label uiLabels[64];
	size_t currentLabelIndex;
};