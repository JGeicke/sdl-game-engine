#pragma once
#include "uielement.h"
#include "panel.h"
#include "SDL.h"

struct Slider : UIElement {
	// function pointer
	typedef void (*eventFunction)(float);
public:
	Slider() {

	}

	Slider(SDL_Renderer* renderer, SDL_Rect background, SDL_Color bgColor, SDL_Color sliderKnobColor,float currentValue) {
		this->background = *(new Panel(renderer, background.x, background.y, background.w, background.h, bgColor));

		if (currentValue > 1.0) currentValue = 1.0f;

		int newX = background.x + (currentValue * background.w);

		this->sliderKnob = *(new Panel(renderer, newX, background.y-5, 10, background.h+10, sliderKnobColor));
	}

	void onValueChanged(eventFunction handler) {
		this->valueChangedHandler = handler;
	}

	SDL_Texture* getBackgroundPanelTexture() {
		return background.getPanelTexture();
	}

	SDL_Rect* getBackgroundPosition() {
		return background.getDisplayPosition();
	}

	SDL_Texture* getSliderKnobPanelTexture() {
		return sliderKnob.getPanelTexture();
	}

	SDL_Rect* getSliderKnobPosition() {
		return sliderKnob.getDisplayPosition();
	}

	int getBackgroundWidth() {
		return background.getWidth();
	}

	void setSliderValue(float newValue) {
		int newX = background.getDisplayPosition()->x + (newValue * background.getWidth());

		this->sliderKnob.setPosition(newX, background.getDisplayPosition()->y-5);

		if (valueChangedHandler != nullptr) {
			//call handler
			valueChangedHandler(newValue);
		}
	}
private:
	eventFunction valueChangedHandler = nullptr;

	Panel sliderKnob;

	Panel background;


};