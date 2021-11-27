#include "uimanager.h"
UIManager::UIManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
    currentFontIndex = 0;
    currentLabelIndex = 0;
    currentProgressBarIndex = 0;
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