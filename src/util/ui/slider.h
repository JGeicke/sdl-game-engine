#pragma once
#include "uielement.h"
#include "panel.h"
#include "SDL.h"
/**
* @brief Struct that represents ui slider.
*/
struct Slider : UIElement {
	// function pointer
	typedef void (*eventFunction)(float);
public:

	/**
	 * @brief Default slider constructor.
	*/
	Slider() {

	}

	/**
	 * @brief Creates a new slider.
	 * @param renderer - Pointer to the renderer.
	 * @param background - Position and size of the background panel.
	 * @param bgColor - Background color.
	 * @param sliderKnobColor - Slideknob color.
	 * @param currentValue - Current value (100%==1.0f).
	*/
	Slider(SDL_Renderer* renderer, SDL_Rect background, SDL_Color bgColor, SDL_Color sliderKnobColor,float currentValue) {
		this->background = *(new Panel(renderer, background.x, background.y, background.w, background.h, bgColor));

		if (currentValue > 1.0) currentValue = 1.0f;

		int newX = (int) (background.x + (currentValue * background.w));

		this->sliderKnob = *(new Panel(renderer, newX, background.y-5, 10, background.h+10, sliderKnobColor));
	}

	/**
	 * @brief Sets the onValueChanged handler function.
	 * @param handler - New onValueChanged handler function.
	*/
	void onValueChanged(eventFunction handler) {
		this->valueChangedHandler = handler;
	}

	/**
	 * @brief Gets the background panel texture.
	 * @return The background panel texture.
	*/
	SDL_Texture* getBackgroundPanelTexture() {
		return background.getPanelTexture();
	}

	/**
	 * @brief Gets the position of the background panel.
	 * @return Position of the background panel.
	*/
	SDL_Rect* getBackgroundPosition() {
		return background.getDisplayPosition();
	}

	/**
	 * @brief Gets the slider knob texture.
	 * @return Texture of the slider knob.
	*/
	SDL_Texture* getSliderKnobPanelTexture() {
		return sliderKnob.getPanelTexture();
	}

	/**
	 * @brief Gets the slider knob position.
	 * @return Position of the slider knob.
	*/
	SDL_Rect* getSliderKnobPosition() {
		return sliderKnob.getDisplayPosition();
	}

	/**
	 * @brief Gets the width of the background texture.
	 * @return Width of the background texture.
	*/
	int getBackgroundWidth() {
		return background.getWidth();
	}

	/**
	 * @brief Sets the current slider value. Adjusts the knob position accordingly.
	 * @param newValue - New slider value.
	*/
	void setSliderValue(float newValue) {
		int newX = (int)(background.getDisplayPosition()->x + (newValue * background.getWidth()));

		this->sliderKnob.setPosition(newX, background.getDisplayPosition()->y-5);

		if (valueChangedHandler != nullptr) {
			//call handler
			valueChangedHandler(newValue);
		}
	}

	/**
	 * @brief Marks the knob as moving.
	 * @param move - Whether the knob is moved by the user.
	*/
	void moveKnob(bool move) {
		isMovingKnob = move;
	}

	/**
	 * @brief Checks if the user is moving the slider knob.
	 * @return Whether the user is moving the slider knob.
	*/
	bool isUserMovingKnob() {
		return isMovingKnob;
	}
private:
	/**
	 * @brief Whether the user is moving the knob.
	*/
	bool isMovingKnob = false;

	/**
	 * @brief OnValueChanged handler function.
	*/
	eventFunction valueChangedHandler = nullptr;

	/**
	 * @brief The slider knob panel of slider.
	*/
	Panel sliderKnob;

	/**
	 * @brief Background panel of slider.
	*/
	Panel background;


};