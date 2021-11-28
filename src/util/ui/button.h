#pragma once
#include "uielement.h"
#include "panel.h"
#include "label.h"
#include "SDL.h"
struct Button: UIElement {
	// function pointer
	typedef void (*clickEventFunction)(void);
public:
	Button(){
		borderWidth = { 0,0 };
		panelColor = { 255,255,255 };
		clickFunction = nullptr;
		hasOnClickFunction = false;
	}
	Button(SDL_Renderer* renderer, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, TTF_Font* font, SDL_Point borderWidth, SDL_Color hoverColor) {
		this->borderWidth = borderWidth;
		this->panelColor = buttonBGColor;
		this->hoverColor = hoverColor;
		buttonLabel = *(new Label(x, y, buttonText, buttonTextColor, renderer, font));
		SDL_Point size;
		SDL_QueryTexture(buttonLabel.getLabelTexture(), NULL, NULL, &size.x, &size.y);
		buttonPanel = *(new Panel(renderer, x-borderWidth.x, y - borderWidth.y, size.x+(borderWidth.x*2), size.y + (borderWidth.y * 2), buttonBGColor));
		hasOnClickFunction = false;
	}

	Button(SDL_Renderer* renderer, const char* panelFilePath, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, TTF_Font* font, SDL_Point borderWidth, SDL_Color hoverColor) {
		this->borderWidth = borderWidth;
		this->panelColor = buttonBGColor;
		this->hoverColor = hoverColor;
		buttonLabel = *(new Label(x, y, buttonText, buttonTextColor, renderer, font));
		SDL_Point size;
		SDL_QueryTexture(buttonLabel.getLabelTexture(), NULL, NULL, &size.x, &size.y);
		buttonPanel = *(new Panel(renderer, panelFilePath,x - borderWidth.x, y - borderWidth.y, size.x+(borderWidth.x*2), size.y + (borderWidth.y * 2), buttonBGColor));
		hasOnClickFunction = false;
	}
	SDL_Texture* getButtonPanel() {
		return buttonPanel.getPanelTexture();
	}

	SDL_Rect* getButtonPanelPosition() {
		return buttonPanel.getDisplayPosition();
	}

	SDL_Texture* getButtonText() {
		return buttonLabel.getLabelTexture();
	}

	SDL_Rect* getButtonTextPosition() {
		return buttonLabel.getDisplayPosition();
	}

	void hover() {
		buttonPanel.setPanelColor(hoverColor);
		hovered = true;
	}

	bool isHovered() {
		return hovered;
	}

	void resetHover() {
		buttonPanel.setPanelColor(panelColor);
	}

	void click() {
		if (hasOnClickFunction) {
			clickFunction();
		}
	}

	void onClick(clickEventFunction click) {
		clickFunction = click;
		hasOnClickFunction = true;
	}
private:
	bool hovered = false;
	SDL_Point borderWidth;
	Label buttonLabel;
	Panel buttonPanel;

	SDL_Color panelColor;
	SDL_Color hoverColor;

	clickEventFunction clickFunction;
	bool hasOnClickFunction;
};