#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "util/ui/label.h"
#include "util/ui/panel.h"

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


	size_t addPanel(const char* filePath, int x, int y, int w, int h);
	size_t addPanel(int x, int y, int w, int h);
	Panel* getPanel(size_t panelIndex) {
		if (panelIndex < currentPanelIndex) {
			return &uiPanels[panelIndex];
		}
	}
	void setPanelPosition(size_t panelIndex, int x, int y);
	void setPanelSize(size_t panelIndex, int w, int h);
	size_t getCurrentPanelIndex() {
		return currentPanelIndex;
	}
private:
	SDL_Renderer* renderer;

	TTF_Font* fonts[3];
	size_t currentFontIndex;

	Label uiLabels[32];
	size_t currentLabelIndex;

	Panel uiPanels[32];
	size_t currentPanelIndex;
};