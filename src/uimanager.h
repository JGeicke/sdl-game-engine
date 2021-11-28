#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "util/ui/label.h"
#include "util/ui/panel.h"
#include "util/ui/progressbar.h"
#include "util/ui/button.h"
#include "inputmanager.h"

/**
 * @brief Manager to manage every ui element.
*/
class UIManager {
public:
	/**
	 * @brief UIManager constructor.
	 * @param renderer - Pointer to the window renderer.
	 * @param inputManager - Pointer to the input manager.
	*/
	UIManager(SDL_Renderer* renderer, InputManager* inputManager);

	/**
	 * @brief UIManager update loop. Used to handle button clicks/hovers.
	*/
	void update();

	/**
	 * @brief Adds a text font.
	 * @param path - Font filepath.
	 * @param fontSize - Fontsize.
	*/
	void addFont(const char* path, int fontSize);

	/**
	 * @brief Adds label to ui.
	 * @param x - X position of label.
	 * @param y - Y position of label.
	 * @param text - Text of label.
	 * @param color - Text color of label.
	 * @param fontIndex - Index of text font.
	 * @return Index of created label.
	*/
	size_t addLabel(int x, int y, std::string text, SDL_Color color, size_t fontIndex);

	/**
	 * @brief Gets label.
	 * @param index - Index of label
	 * @return Pointer to label.
	*/
	Label* getLabel(size_t index) {
		if (index < currentLabelIndex) {
			return &uiLabels[index];
		}
	}
	/**
	 * @brief Gets current label index.
	 * @return Current label index.
	*/
	size_t getCurrentLabelIndex() {
		return currentLabelIndex;
	}

	/**
	 * @brief Adds panel to ui.
	 * @param filePath - File path to texture file.
	 * @param x - X position of panel.
	 * @param y - Y position of panel.
	 * @param w - Width of panel.
	 * @param h - Height of panel.
	 * @param panelColor - Background color of panel.
	 * @return Index of created panel.
	*/
	size_t addPanel(const char* filePath, int x, int y, int w, int h, SDL_Color panelColor);
	/**
	 * @brief Adds panel to ui.
	 * @param x - X position of panel.
	 * @param y - Y position of panel.
	 * @param w - Width of panel.
	 * @param h - Height of panel.
	 * @param panelColor - Background color of panel.
	 * @return Index of created panel.
	*/
	size_t addPanel(int x, int y, int w, int h, SDL_Color panelColor);
	/**
	 * @brief Gets panel.
	 * @param panelIndex - Index of panel.
	 * @return Pointer to panel.
	*/
	Panel* getPanel(size_t panelIndex) {
		if (panelIndex < currentPanelIndex) {
			return &uiPanels[panelIndex];
		}
	}
	/**
	 * @brief Gets current panel index.
	 * @return Current panel index.
	*/
	size_t getCurrentPanelIndex() {
		return currentPanelIndex;
	}

	/**
	 * @brief Adds progressbar to ui.
	 * @param bgFilePath - File path to background texture.
	 * @param progressFilePath - File path to progress texture.
	 * @param x - X position of progressbar.
	 * @param y - Y position of progressbar.
	 * @param w - Width of progressbar.
	 * @param h - Height of progressbar.
	 * @param bgColor - Color of background texture.
	 * @param progressColor - Color of progress texture.
	 * @return Index of created progressbar.
	*/
	size_t addProgressBar(const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor);
	/**
	 * @brief Adds progressbar to ui.
	 * @param x - X position of progressbar.
	 * @param y - Y position of progressbar.
	 * @param w - Width of progressbar.
	 * @param h - Height of progressbar.
	 * @param bgColor - Color of background texture.
	 * @param progressColor - Color of progress texture.
	 * @return Index of created progressbar.
	*/
	size_t addProgressBar(int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor);
	/**
	 * @brief Gets progressbar.
	 * @param progressBarIndex - Index of progressbar.
	 * @return Pointer to progressbar.
	*/
	ProgressBar* getProgressBar(size_t progressBarIndex) {
		if (progressBarIndex < currentProgressBarIndex) {
			return &uiProgressBars[progressBarIndex];
		}
	}
	/**
	 * @brief Gets current progressbar index.
	 * @return Current progressbar index.
	*/
	size_t getCurrentProgressBarIndex() {
		return currentProgressBarIndex;
	}

	/**
	 * @brief Adds button to ui.
	 * @param x - X position of button
	 * @param y - Y position of button
	 * @param buttonText - Text of button label.
	 * @param buttonTextColor  - Textcolor of button label.
	 * @param buttonBGColor - Color of button background texture.
	 * @param fontIndex - Index of font.
	 * @param borderWidth - Borderwidth of button
	 * @param hoverColor - Hover color of button background texture.
	 * @return Index of created button.
	*/
	size_t addButton(int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor);
	/**
	 * @brief Adds button to ui.
	 * @param panelFilePath - File path to background texture.
	 * @param x - X position of button
	 * @param y - Y position of button
	 * @param buttonText - Text of button label.
	 * @param buttonTextColor  - Textcolor of button label.
	 * @param buttonBGColor - Color of button background texture.
	 * @param fontIndex - Index of font.
	 * @param borderWidth - Borderwidth of button
	 * @param hoverColor - Hover color of button background texture.
	 * @return Index of created button.
	*/
	size_t addButton(const char* panelFilePath, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor);

	/**
	 * @brief Gets button.
	 * @param buttonIndex - Index of button.
	 * @return Pointer to button.
	*/
	Button* getButton(size_t buttonIndex) {
		if (buttonIndex < currentButtonIndex) {
			return &uiButtons[buttonIndex];
		}
	}
	/**
	 * @brief Gets current button index.
	 * @return Current button index.
	*/
	size_t getCurrentButtonIndex() {
		return currentButtonIndex;
	}
private:
	/**
	 * @brief Pointer to window renderer.
	*/
	SDL_Renderer* renderer;
	/**
	 * @brief Pointer to user input manager.
	*/
	InputManager* inputManager;

	/**
	 * @brief Loaded fonts.
	*/
	TTF_Font* fonts[3];
	/**
	 * @brief Current font count.
	*/
	size_t currentFontIndex;

	/**
	 * @brief Array of created ui labels.
	*/
	Label uiLabels[32];
	/**
	 * @brief Current label count.
	*/
	size_t currentLabelIndex;

	/**
	 * @brief Array of created ui panels.
	*/
	Panel uiPanels[32];
	/**
	 * @brief Current panel count.
	*/
	size_t currentPanelIndex;

	/**
	 * @brief Array of created ui progressbars.
	*/
	ProgressBar uiProgressBars[32];
	/**
	 * @brief Current progressbar count.
	*/
	size_t currentProgressBarIndex;

	/**
	 * @brief Array of created ui buttons.
	*/
	Button uiButtons[32];
	/**
	 * @brief Current button count.
	*/
	size_t currentButtonIndex;

	/**
	 * @brief Checks if any buttons are hovered or clicked.
	*/
	void checkButtons();
};