#pragma once
#include "SDL_ttf.h"
#include "string"
#include "uielement.h"
/**
 * @brief Struct that represents ui labels.
*/
struct Label: UIElement {
public:
	/**
	 * @brief Default label constructor.
	*/
	Label(){
		displayPosition = { 0,0,0,0 };
		labelTexture = nullptr;
		textFont = nullptr;
		textColor = { 255,255,255 };
	}

	/**
	 * @brief Creates new label.
	 * @param x - X position of the label.
	 * @param y - Y position of the label.
	 * @param labelText - Text of the label.
	 * @param color - Text color.
	 * @param renderer - Pointer to the window renderer
	 * @param font - Textfont of the label.
	*/
	Label(int x, int y, std::string labelText, SDL_Color& color, SDL_Renderer* renderer, TTF_Font* font){
		this->text = labelText;
		this->textColor = color;
		this->textFont = font;

		setPosition(x, y);
		createLabelTexture(renderer);
	}

	/**
	* @brief Deconstructor of label.
	*/
	~Label(){
		SDL_DestroyTexture(labelTexture);
	}

	/**
	 * @brief Sets label text.
	 * @param text - New label text.
	 * @param renderer - Pointer to the window renderer.
	*/
	void setText(std::string text, SDL_Renderer* renderer) {
		this->text = text;
		createLabelTexture(renderer);
	}

	/**
	 * @brief Sets the label position.
	 * @param x - New x position.
	 * @param y - New y position.
	*/
	void setPosition(int x, int y) {
		displayPosition.x = x;
		displayPosition.y = y;
	}

	/**
	 * @brief Sets the text color of the label.
	 * @param color - New text color.
	 * @param renderer - Pointer to the window renderer.
	*/
	void setTextColor(SDL_Color color, SDL_Renderer* renderer) {
		this->textColor = color;
		createLabelTexture(renderer);
	}

	/**
	 * @brief Gets the label texture.
	 * @return Pointer to the label texture.
	*/
	SDL_Texture* getLabelTexture() {
		return labelTexture;
	}

	/**
	 * @brief Gets the display position of the label.
	 * @return Pointer to the display position.
	*/
	SDL_Rect* getDisplayPosition() {
		return &displayPosition;
	}
private:
	/**
	 * @brief Position where the label will be displayed on screen.
	*/
	SDL_Rect displayPosition;
	/**
	 * @brief Text color.
	*/
	SDL_Color textColor;
	/**
	 * @brief Textfont.
	*/
	TTF_Font* textFont;
	/**
	 * @brief Texture of label.
	*/
	SDL_Texture* labelTexture;
	/**
	 * @brief Current text of label.
	*/
	std::string text;

	/**
	 * @brief Creates a new texture based on the current text.
	 * @param renderer - Pointer to the window renderer.
	*/
	void createLabelTexture(SDL_Renderer* renderer) {
		SDL_Surface* tempSurface = TTF_RenderText_Blended(textFont, text.c_str(), textColor);
		this->labelTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		SDL_QueryTexture(labelTexture, NULL, NULL, &displayPosition.w, &displayPosition.h);
	}
};
