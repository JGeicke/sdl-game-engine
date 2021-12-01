#include "uimanager.h"
// TODO: max elements handling
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
}

/**
* @brief Adds a text font.
* @param path - Font filepath.
* @param fontSize - Fontsize.
*/
void UIManager::addFont(const char* path, int fontSize){
    fonts[currentFontIndex] = TTF_OpenFont(path, fontSize);
    if (!fonts[currentFontIndex]) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", TTF_GetError(), NULL);
        return;
    }

    currentFontIndex++;
}
#pragma region Label
/**
* @brief Adds label to ui.
* @param x - X position of label.
* @param y - Y position of label.
* @param text - Text of label.
* @param color - Text color of label.
* @param fontIndex - Index of text font.
* @return Index of created label. -1 if no label was created.
*/
size_t UIManager::addLabel(int x, int y, std::string text, SDL_Color color, size_t fontIndex){
    if (fontIndex < currentFontIndex) {
        uiLabels[currentLabelIndex] = *(new Label(x, y, text, color, renderer, fonts[fontIndex]));
        return currentLabelIndex++;
    }
    return -1;
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
* @return Index of created panel.
*/
size_t UIManager::addPanel(const char* filePath, int x, int y, int w, int h, SDL_Color panelColor) {
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
* @return Index of created panel.
*/
size_t UIManager::addPanel(int x, int y, int w, int h, SDL_Color panelColor){
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
* @return Index of created progressbar.
*/
size_t UIManager::addProgressBar(const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor){
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
* @return Index of created progressbar.
*/
size_t UIManager::addProgressBar(int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
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
* @return Index of created button. -1 if no button was created.
*/
size_t UIManager::addButton(int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor){
    if (fontIndex < currentFontIndex) {
        uiButtons[currentButtonIndex] = *(new Button(renderer,x,y,buttonText, buttonTextColor, buttonBGColor, fonts[fontIndex], borderWidth, hoverColor));
        return currentButtonIndex++;
    }
    return -1;
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
* @return Index of created button.
*/
size_t UIManager::addButton(const char* panelFilePath, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor) {
    if (fontIndex < currentFontIndex) {
        uiButtons[currentButtonIndex] = *(new Button(renderer, panelFilePath, x, y, buttonText, buttonTextColor, buttonBGColor, fonts[fontIndex], borderWidth, hoverColor));
        return currentButtonIndex++;
    }
    return -1;
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