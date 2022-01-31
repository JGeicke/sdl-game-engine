#include "uimanager.h"
/**
* @brief UIManager constructor.
* @param renderer - Pointer to the window renderer.
* @param inputManager - Pointer to the input manager.
*/
UIManager::UIManager(SDL_Renderer* renderer, InputManager* inputManager) {
    this->renderer = renderer;
    this->inputManager = inputManager;

    currentFontIndex = 0;
    currentLabelIndex = 0;
    currentPanelIndex = 0;
    currentProgressBarIndex = 0;
    currentButtonIndex = 0;
    currentSliderIndex = 0;
}

/**
* @brief Destructor of UI manager.
*/
UIManager::~UIManager() {
    for (size_t i = 0; i < currentFontIndex; i++)
    {
        TTF_CloseFont(fonts[i]);
    }
}

/**
* @brief UIManager update loop. Used to handle button clicks/hovers.
*/
void UIManager::update() {
    checkButtons();
    checkSliders();
}

/**
* @brief Adds a text font.
* @param path - Font filepath.
* @param fontSize - Fontsize.
* @return Index of created font. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addFont(const char* path, int fontSize){
    if (currentFontIndex == 8) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't load anymore fonts.", NULL);
        return SIZE_MAX;
    }

    fonts[currentFontIndex] = TTF_OpenFont(path, fontSize);
    if (!fonts[currentFontIndex]) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", TTF_GetError(), NULL);
        return SIZE_MAX;
    }

    return currentFontIndex++;
}

/**
* @brief Clears every ui element present.
*/
void UIManager::clearUI() {
    currentLabelIndex = 0;
    currentButtonIndex = 0;
    currentPanelIndex = 0;
    currentProgressBarIndex = 0;
    currentSliderIndex = 0;
}

#pragma region Label
/**
* @brief Adds label to ui.
* @param x - X position of label.
* @param y - Y position of label.
* @param text - Text of label.
* @param color - Text color of label.
* @param fontIndex - Index of text font.
* @return Index of created label. -1 if no label was created. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addLabel(int x, int y, std::string text, SDL_Color color, size_t fontIndex){
    if (currentLabelIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore labels.", NULL);
    } else if (fontIndex < currentFontIndex) {
        uiLabels[currentLabelIndex] = *(new Label(x, y, text, color, renderer, fonts[fontIndex]));
        return currentLabelIndex++;
    }
    return SIZE_MAX;
}
#pragma endregion Label

#pragma region Panel
/**
* @brief Adds panel to ui.
* @param filePath - File path to texture file.
* @param x - X position of panel.
* @param y - Y position of panel.
* @param w - Width of panel.
* @param h - Height of panel.
* @param panelColor - Background color of panel.
* @return Index of created panel. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addPanel(const char* filePath, int x, int y, int w, int h, SDL_Color panelColor) {
    if (currentPanelIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore panels.", NULL);
        return SIZE_MAX;
    }
    uiPanels[currentPanelIndex] = *(new Panel(renderer,filePath, x, y, w, h, panelColor));
    return currentPanelIndex++;
}

/**
* @brief Adds panel to ui.
* @param x - X position of panel.
* @param y - Y position of panel.
* @param w - Width of panel.
* @param h - Height of panel.
* @param panelColor - Background color of panel.
* @return Index of created panel. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addPanel(int x, int y, int w, int h, SDL_Color panelColor){
    if (currentPanelIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore panels.", NULL);
        return SIZE_MAX;
    }
    uiPanels[currentPanelIndex] = *(new Panel(renderer, x, y, w, h, panelColor));
    return currentPanelIndex++;
}
#pragma endregion Panel

#pragma region ProgressBar
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
* @return Index of created progressbar. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addProgressBar(const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor){
    if (currentProgressBarIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore progress bars.", NULL);
        return SIZE_MAX;
    }
    uiProgressBars[currentProgressBarIndex] = *(new ProgressBar(renderer, bgFilePath, progressFilePath, x, y, w, h, bgColor, progressColor));
    return currentProgressBarIndex++;
}

/**
* @brief Adds progressbar to ui.
* @param x - X position of progressbar.
* @param y - Y position of progressbar.
* @param w - Width of progressbar.
* @param h - Height of progressbar.
* @param bgColor - Color of background texture.
* @param progressColor - Color of progress texture.
* @return Index of created progressbar. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addProgressBar(int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
    if (currentProgressBarIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore progress bars.", NULL);
        return SIZE_MAX;
    }
    uiProgressBars[currentProgressBarIndex] = *(new ProgressBar(renderer, x, y, w, h, bgColor, progressColor));
    return currentProgressBarIndex++;
}
#pragma endregion ProgressBar

#pragma region Button
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
* @return Index of created button. -1 if no button was created. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addButton(int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor){
    if (currentButtonIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore buttons.", NULL);
    }else if (fontIndex < currentFontIndex) {
        uiButtons[currentButtonIndex] = *(new Button(renderer,x,y,buttonText, buttonTextColor, buttonBGColor, fonts[fontIndex], borderWidth, hoverColor));
        return currentButtonIndex++;
    }
    return SIZE_MAX;
}

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
* @return Index of created button. When unsuccesful, returns SIZE_MAX. 
*/
size_t UIManager::addButton(const char* panelFilePath, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor) {
    if (currentButtonIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore buttons.", NULL);
    }else if (fontIndex < currentFontIndex) {
        uiButtons[currentButtonIndex] = *(new Button(renderer, panelFilePath, x, y, buttonText, buttonTextColor, buttonBGColor, fonts[fontIndex], borderWidth, hoverColor));
        return currentButtonIndex++;
    }
    return SIZE_MAX;
}

/**
* @brief Checks if any buttons are hovered or clicked by comparing the mouse position to the button panel position.
*/
void UIManager::checkButtons() {
    SDL_Point mousePosition = {0,0};
    for (size_t i = 0; i < currentButtonIndex; i++) {
        Button* nextButton = getButton(i);
        if (nextButton->isVisible()) {
            SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
            SDL_Rect* buttonPanelPosition = nextButton->getButtonPanelPosition();

            if (SDL_PointInRect(&mousePosition, buttonPanelPosition) == SDL_TRUE) {
               if (inputManager->getMouseButton() == SDL_BUTTON_LEFT) {
                    nextButton->click();
               }
                nextButton->hover();
            }
            else if (nextButton->isHovered()) {
                // reset hover
                nextButton->resetHover();
            }
        }
    }
}
#pragma endregion Button
#pragma region Sliders
/**
* @brief Adds slider to the ui.
* @param background - Position and size of the background panel.
* @param bgColor - Background color.
* @param sliderKnobColor - Color of the slider knob.
* @param currentVal - Current slider value.
* @return Index of the slider.
*/
size_t UIManager::addSlider(SDL_Rect background, SDL_Color bgColor, SDL_Color sliderKnobColor, float currentVal) {
    if (currentSliderIndex == 32) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", "Can't create anymore sliders.", NULL);
        return SIZE_MAX;
    }
    uiSliders[currentSliderIndex] = *(new Slider(renderer, background, bgColor, sliderKnobColor, currentVal));
    return currentSliderIndex++;
}

/**
* @brief Checks if any sliders are clicked.
*/
void UIManager::checkSliders() {
    SDL_Point mousePosition = { 0,0 };
    for (size_t i = 0; i < currentSliderIndex; i++) {
        Slider* nextSlider = getSlider(i);
        if (nextSlider->isVisible()) {
            SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
            SDL_Rect* sliderBGPosition = nextSlider->getBackgroundPosition();

            if (SDL_PointInRect(&mousePosition,sliderBGPosition) == SDL_TRUE) {
                if (inputManager->getMouseButton() == SDL_BUTTON_LEFT) {
                    nextSlider->moveKnob(!nextSlider->isUserMovingKnob());
                }

                // check if user is moving current slider
                if (nextSlider->isUserMovingKnob()) {
                    int offset = mousePosition.x - sliderBGPosition->x;
                    float val = (float)offset / nextSlider->getBackgroundWidth();
                    float newSliderValue = std::roundf(val * 100) / 100;
                    nextSlider->setSliderValue(newSliderValue);
                }
            }
            else {
                // reset if no intersection with mouse
                if (nextSlider->isUserMovingKnob()) {
                    nextSlider->moveKnob(false);
                }
            }
        }
    }
}
#pragma endregion Sliders