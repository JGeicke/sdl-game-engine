#include "uimanager.h"
UIManager::UIManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
    currentFontIndex = 0;
    currentLabelIndex = 0;
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

void UIManager::setLabelText(size_t labelIndex, std::string labelText) {
    if (labelIndex < currentLabelIndex) {
        uiLabels[labelIndex].setText(labelText, renderer);
    }
}
void UIManager::setLabelPosition(size_t labelIndex, int x, int y) {
    if (labelIndex < currentLabelIndex) {
        uiLabels[labelIndex].setPosition(x, y);
    }
}

void UIManager::setLabelTextColor(size_t labelIndex, SDL_Color textColor) {
    if (labelIndex < currentLabelIndex) {
        uiLabels[labelIndex].setTextColor(textColor, renderer);
    }
}
#pragma endregion Label

#pragma region Panel
size_t UIManager::addPanel(const char* filePath, int x, int y, int w, int h) {
    uiPanels[currentPanelIndex] = *(new Panel(renderer,filePath, x, y, w, h));
    return currentPanelIndex++;
}
size_t UIManager::addPanel(int x, int y, int w, int h){
    uiPanels[currentPanelIndex] = *(new Panel(renderer, x, y, w, h));
    return currentPanelIndex++;
}
void UIManager::setPanelPosition(size_t panelIndex, int x, int y){
    if (panelIndex < currentPanelIndex) {
        uiPanels[panelIndex].setPosition(x, y);
    }
}
void UIManager::setPanelSize(size_t panelIndex, int w, int h) {
    if (panelIndex < currentPanelIndex) {
        uiPanels[panelIndex].setSize(w, h);
    }
}
#pragma endregion Panel