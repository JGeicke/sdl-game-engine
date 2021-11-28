#include "uimanager.h"
// TODO: max elements handling
UIManager::UIManager(SDL_Renderer* renderer, InputManager* inputManager) {
    this->renderer = renderer;
    this->inputManager = inputManager;
    currentFontIndex = 0;
    currentLabelIndex = 0;
    currentPanelIndex = 0;
    currentProgressBarIndex = 0;
    currentButtonIndex = 0;
}

void UIManager::update() {
    checkButtons();
}

void UIManager::addFont(const char* path, int fontSize){
    fonts[currentFontIndex] = TTF_OpenFont(path, fontSize);
    if (!fonts[currentFontIndex]) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL TTF Error", TTF_GetError(), NULL);
        return;
    }

    currentFontIndex++;
}
#pragma region Label
size_t UIManager::addLabel(int x, int y, std::string text, SDL_Color color, size_t fontIndex){
    if (fontIndex < currentFontIndex) {
        uiLabels[currentLabelIndex] = *(new Label(x, y, text, color, renderer, fonts[fontIndex]));
        return currentLabelIndex++;
    }
}
#pragma endregion Label

#pragma region Panel
size_t UIManager::addPanel(const char* filePath, int x, int y, int w, int h, SDL_Color panelColor) {
    uiPanels[currentPanelIndex] = *(new Panel(renderer,filePath, x, y, w, h, panelColor));
    return currentPanelIndex++;
}
size_t UIManager::addPanel(int x, int y, int w, int h, SDL_Color panelColor){
    uiPanels[currentPanelIndex] = *(new Panel(renderer, x, y, w, h, panelColor));
    return currentPanelIndex++;
}
#pragma endregion Panel

#pragma region ProgressBar
size_t UIManager::addProgressBar(const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor){
    uiProgressBars[currentProgressBarIndex] = *(new ProgressBar(renderer, bgFilePath, progressFilePath, x, y, w, h, bgColor, progressColor));
    return currentProgressBarIndex++;
}
size_t UIManager::addProgressBar(int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
    uiProgressBars[currentProgressBarIndex] = *(new ProgressBar(renderer, x, y, w, h, bgColor, progressColor));
    return currentProgressBarIndex++;
}
#pragma endregion ProgressBar

#pragma region Button
size_t UIManager::addButton(int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor){
    if (fontIndex < currentFontIndex) {
        uiButtons[currentButtonIndex] = *(new Button(renderer,x,y,buttonText, buttonTextColor, buttonBGColor, fonts[fontIndex], borderWidth, hoverColor));
        return currentButtonIndex++;
    }
}
size_t UIManager::addButton(const char* panelFilePath, int x, int y, std::string buttonText, SDL_Color buttonTextColor, SDL_Color buttonBGColor, size_t fontIndex, SDL_Point borderWidth, SDL_Color hoverColor) {
    if (fontIndex < currentFontIndex) {
        uiButtons[currentButtonIndex] = *(new Button(renderer, panelFilePath, x, y, buttonText, buttonTextColor, buttonBGColor, fonts[fontIndex], borderWidth, hoverColor));
        return currentButtonIndex++;
    }
}

void UIManager::checkButtons() {
    SDL_Point mousePosition;
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