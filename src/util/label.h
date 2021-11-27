#pragma once
#include "SDL_ttf.h"
#include "string"
struct Label {
public:
	Label(){}

	Label(int x, int y, std::string labelText, SDL_Color& color, SDL_Renderer* renderer, TTF_Font* font){
		this->text = labelText;
		this->textColor = color;
		this->textFont = font;

		setPosition(x, y);
		createLabelTexture(renderer);
	}

	~Label(){}

	void setText(std::string text, SDL_Renderer* renderer) {
		this->text = text;
		createLabelTexture(renderer);
	}

	void setPosition(int x, int y) {
		displayPosition.x = x;
		displayPosition.y = y;
	}

	void setTextColor(SDL_Color color, SDL_Renderer* renderer) {
		this->textColor = color;
		createLabelTexture(renderer);
	}

	SDL_Texture* getLabelTexture() {
		return labelTexture;
	}

	SDL_Rect* getDisplayPosition() {
		return &displayPosition;
	}
private:
	SDL_Rect displayPosition;
	SDL_Color textColor;
	TTF_Font* textFont;
	SDL_Texture* labelTexture;

	std::string text;

	void createLabelTexture(SDL_Renderer* renderer) {
		SDL_Surface* tempSurface = TTF_RenderText_Blended(textFont, text.c_str(), textColor);
		this->labelTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);

		SDL_QueryTexture(labelTexture, NULL, NULL, &displayPosition.w, &displayPosition.h);
	}
};
