#pragma once
#include "uielement.h"
#include "panel.h"
#include "label.h"
#include "SDL.h"
/**
* @brief Struct that represents ui buttons.
*/
struct Button: UIElement {
	// function pointer
	typedef void (*clickEventFunction)(void);
public:
	/**
	 * @brief Default button constructor.
	*/
	Button(){
		borderWidth = { 0,0 };
		panelColor = { 255,255,255 };
		clickFunction = nullptr;
		hasOnClickFunction = false;
		hoverColor = {200,200,200};
	}
	/**
	 * @brief Creates new button.
	 * @param renderer - Pointer to window renderer.
	 * @param x - X position of button.
	 * @param y - Y position of button.
	 * @param buttonText - Button text.
	 * @param buttonTextColor - Textcolor.
	 * @param buttonBGColor - Color of button background texture.
	 * @param font - Textfont.
	 * @param borderWidth - Width of button border.
	 * @param hoverColor - Color of button background texture when hovered
	*/
	Button(SDL_Renderer* renderer, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, TTF_Font* font, SDL_Point borderWidth, SDL_Color hoverColor) {
		this->borderWidth = borderWidth;
		this->panelColor = buttonBGColor;
		this->hoverColor = hoverColor;
		buttonLabel = *(new Label(x, y, buttonText, buttonTextColor, renderer, font));
		SDL_Point size;
		SDL_QueryTexture(buttonLabel.getLabelTexture(), NULL, NULL, &size.x, &size.y);
		buttonPanel = *(new Panel(renderer, x- (size.x/2) - borderWidth.x, y -(size.y/2) - borderWidth.y, size.x+(borderWidth.x*2), size.y + (borderWidth.y * 2), buttonBGColor));
		hasOnClickFunction = false;
	}

	/**
	 * @brief Creates new button.
	 * @param renderer - Pointer to window renderer.
	 * @param panelFilePath - 
	 * @param x - X position of button.
	 * @param y - Y position of button.
	 * @param buttonText - Button text.
	 * @param buttonTextColor - Textcolor.
	 * @param buttonBGColor - Color of button background texture.
	 * @param font - Textfont.
	 * @param borderWidth - Width of button border.
	 * @param hoverColor - Color of button background texture when hovered
	*/
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

	/**
	 * @brief Gets the button panel texture.
	 * @return Pointer to the button panel texture.
	*/
	SDL_Texture* getButtonPanel() {
		return buttonPanel.getPanelTexture();
	}

	/**
	 * @brief Gets the button panel position.
	 * @return Pointer to the button panel position.
	*/
	SDL_Rect* getButtonPanelPosition() {
		return buttonPanel.getDisplayPosition();
	}

	/**
	 * @brief Gets the button label texture.
	 * @return - Pointer to the button label texture.
	*/
	SDL_Texture* getButtonText() {
		return buttonLabel.getLabelTexture();
	}

	/**
	 * @brief Gets the button label position.
	 * @return - Pointer to the button label position.
	*/
	SDL_Rect* getButtonTextPosition() {
		return buttonLabel.getDisplayPosition();
	}

	/**
	 * @brief Hovers the button. Changes button background texture color and marks the button as hovered.
	*/
	void hover() {
		buttonPanel.setPanelColor(hoverColor);
		hovered = true;
	}

	/**
	 * @brief Checks if the button is hovered.
	 * @return - Whether the button is hovered.
	*/
	bool isHovered() {
		return hovered;
	}

	/**
	 * @brief Resets the hover. Changes button background texture color back to default.
	*/
	void resetHover() {
		buttonPanel.setPanelColor(panelColor);
	}
	
	/**
	 * @brief Calls the click handler function of the button. Called when the button is clicked.
	*/
	void click() {
		if (hasOnClickFunction) {
			clickFunction();
		}
	}

	/**
	 * @brief Adds click handler function to the button.
	 * @param click - Click handler.
	*/
	void onClick(clickEventFunction click) {
		clickFunction = click;
		hasOnClickFunction = true;
	}
private:
	/**
	 * @brief Whether the button is hovered.
	*/
	bool hovered = false;
	/**
	 * @brief Border width of the button.
	*/
	SDL_Point borderWidth;
	/**
	 * @brief Buttontext label.
	*/
	Label buttonLabel;
	/**
	 * @brief Button background panel.
	*/
	Panel buttonPanel;

	/**
	 * @brief Default panel texture color.
	*/
	SDL_Color panelColor;
	/**
	 * @brief Panel texture color when the button is hovered.
	*/
	SDL_Color hoverColor;

	/**
	 * @brief Function pointer to the click handler function.
	*/
	clickEventFunction clickFunction;
	/**
	 * @brief Whether the button has a click handler function registered.
	*/
	bool hasOnClickFunction;
};