#pragma once
#include "SDL.h"
#include "../fileloader.h"
/**
* @brief Struct that represents ui progressbars.
*/
struct ProgressBar: UIElement {
public:
	/**
	 * @brief Default progressbar constructor.
	*/
	ProgressBar() {
		progress = 0.0f;
	}

	/**
	 * @brief Creates new progressbar.
	 * @param renderer - Pointer to the window renderer.
	 * @param bgFilePath - File path to the background texture.
	 * @param progressFilePath - File path to the progress texture.
	 * @param x - X position of the progressbar.
	 * @param y - Y position of the progressbar.
	 * @param w - Width of the progressbar.
	 * @param h - Height of the progressbar.
	 * @param bgColor - Color of the background texture.
	 * @param progressColor - Color of the progress texture. 
	*/
	ProgressBar(SDL_Renderer* renderer, const char* bgFilePath, const char* progressFilePath, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
		progressPanel = *(new Panel(renderer, progressFilePath, x,y,w,h,progressColor));
		progressPanel.setPosition(x, y);
		backgroundPanel = *(new Panel(renderer, bgFilePath, x, y, w, h, bgColor));
		backgroundPanel.setPosition(x, y);

		progressPanel.setPanelColor(progressColor);
		backgroundPanel.setPanelColor(bgColor);

		progress = 0.0f;
	}

	/**
	 * @brief Creates new progressbar.
	 * @param renderer - Pointer to the window renderer.
	 * @param x - X position of the progressbar.
	 * @param y - Y position of the progressbar.
	 * @param w - Width of the progressbar.
	 * @param h - Height of the progressbar.
	 * @param bgColor - Color of the background texture.
	 * @param progressColor - Color of the progress texture. 
	*/
	ProgressBar(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color bgColor, SDL_Color progressColor) {
		progressPanel = *(new Panel(renderer, x, y, w, h, progressColor));
		progressPanel.setPosition(x, y);
		backgroundPanel = *(new Panel(renderer, x, y, w, h, bgColor));
		backgroundPanel.setPosition(x, y);

		progressPanel.setPanelColor(progressColor);
		backgroundPanel.setPanelColor(bgColor);

		progress = 0.0f;
	}

	/**
	 * @brief Sets the position of the progressbar.
	 * @param x - New x position.
	 * @param y - New y position.
	*/
	void setPosition(int x, int y) {
		progressPanel.setPosition(x, y);
		backgroundPanel.setPosition(x, y);
	}

	/**
	 * @brief Sets the size of the progressbar.
	 * @param w - Width of the progressbar.
	 * @param h - Height of the progressbar.
	*/
	void setSize(int w, int h) {
		backgroundPanel.setSize(w, h);
		progressPanel.setHeight(h);
	}

	/**
	 * @brief Sets current progress of the progressbar.
	 * @param progress - Current progress of the progressbar (1.0 = 100% progress)
	*/
	void setProgress(float progress) {
		this->progress = progress;
		progressPanel.setWidth((int)backgroundPanel.getWidth() * progress);
	}

	/**
	 * @brief Sets the color of the background texture.
	 * @param color - New color.
	*/
	void setBackgroundColor(SDL_Color color) {
		backgroundPanel.setPanelColor(color);
	}

	/**
	 * @brief Sets the color of the progress texture.
	 * @param color - New color.
	*/
	void setProgressColor(SDL_Color color) {
		progressPanel.setPanelColor(color);
	}

	/**
	 * @brief Gets the background texture of the progressbar.
	 * @return Pointer to the background texture.
	*/
	SDL_Texture* getBackgroundTexture() {
		return backgroundPanel.getPanelTexture();
	}

	/**
	 * @brief Gets the position of the progressbar background.
	 * @return Pointer to the background position.
	*/
	SDL_Rect* getBackgroundPosition() {
		return backgroundPanel.getDisplayPosition();
	}

	/**
	 * @brief Gets the progress texture of the progressbar.
	 * @return Pointer to the progress texture.
	*/
	SDL_Texture* getProgressTexture() {
		return progressPanel.getPanelTexture();
	}

	/**
	 * @brief Gets the position of the progressbar progress.
	 * @return Pointer to the progress position.
	*/
	SDL_Rect* getProgressPosition() {
		return progressPanel.getDisplayPosition();
	}
private:
	/**
	 * @brief Progresspanel.
	*/
	Panel progressPanel;
	/**
	 * @brief Backgroundpanel.
	*/
	Panel backgroundPanel;

	/**
	 * @brief Current progress.
	*/
	float progress;
};