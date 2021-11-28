#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "../fileloader.h"
#include "uielement.h"
/**
* @brief Struct that represents ui labels.
*/
struct Panel: UIElement {
public:

	/**
	 * @brief Default panel constructor.
	*/
	Panel() {
		panelTexture = nullptr;
		displayPosition = {0,0,0,0};
	}

	/**
	* @brief Deconstructor of panel.
	*/
	~Panel() {
		SDL_DestroyTexture(panelTexture);
	}

	/**
	 * @brief Creates new panel.
	 * @param renderer - Pointer to the window renderer.
	 * @param filePath - File path to the panel texture.
	 * @param x - X position of the panel.
	 * @param y - Y position of the panel.
	 * @param w - Width of the panel.
	 * @param h - Height of the panel.
	 * @param panelColor - Color of the panel texture.
	*/
	Panel(SDL_Renderer* renderer, const char* filePath, int x, int y, int w, int h, SDL_Color panelColor) {
		setPosition(x, y);
		setSize(w, h);

		this->panelTexture = FileLoader::loadSDLTexture(filePath, renderer);
		setPanelColor(panelColor);
	}

	/**
	 * @brief Creates new panel.
	 * @param renderer - Pointer to the window renderer.
	 * @param x - X position of the panel.
	 * @param y - Y position of the panel.
	 * @param w - Width of the panel.
	 * @param h - Height of the panel.
	 * @param panelColor - Color of the panel texture.
	*/
	Panel(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color panelColor) {
		setPosition(x, y);
		setSize(w, h);

		// use base panel texture
		this->panelTexture = FileLoader::loadSDLTexture("assets/base_panel.png", renderer);
		setPanelColor(panelColor);
	}

	/**
	 * @brief Sets position of the panel.
	 * @param x - New x position.
	 * @param y - New y position.
	*/
	void setPosition(int x, int y) {
		displayPosition.x = x;
		displayPosition.y = y;
	}

	/**
	 * @brief Sets the size of the panel.
	 * @param w - New panel width.
	 * @param h - New panel height.
	*/
	void setSize(int w, int h) {
		displayPosition.w = w;
		displayPosition.h = h;
	}

	/**
	 * @brief Sets the width of the panel.
	 * @param w - New panel width.
	*/
	void setWidth(int w) {
		displayPosition.w = w;
	}

	/**
	 * @brief Sets the height of the panel.
	 * @param h - New panel height.
	*/
	void setHeight(int h) {
		displayPosition.h = h;
	}

	/**
	 * @brief Gets the panel texture.
	 * @return Pointer to the panel texture.
	*/
	SDL_Texture* getPanelTexture() {
		return panelTexture;
	}

	/**
	 * @brief Gets the display position of the panel.
	 * @return Pointer to the display positon.
	*/
	SDL_Rect* getDisplayPosition() {
		return &displayPosition;
	}

	/**
	 * @brief Gets current panel width.
	 * @return Width of the panel.
	*/
	int getWidth() {
		return displayPosition.w;
	}

	/**
	 * @brief Sets the current color of the panel texture.
	 * @param color - New color of the panel texture.
	*/
	void setPanelColor(SDL_Color color) {
		SDL_SetTextureColorMod(panelTexture, color.r, color.g, color.b);
	}
private:
	/**
	 * @brief Texture of the panel.
	*/
	SDL_Texture* panelTexture;
	/**
	 * @brief Position where the panel will be displayed on screen.
	*/
	SDL_Rect displayPosition;
};