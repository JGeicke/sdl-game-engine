#pragma once
/**
 * @brief Base ui element.
*/
struct UIElement {
public:
	/**
	 * @brief Whether the ui element is visibile. Elements not visible are not rendered.
	 * @return Whether the ui element is visible.
	*/
	bool isVisible() {
		return visible;
	}

	/**
	 * @brief Sets the visibility of the ui element.
	 * @param show - Whether the ui element is visible.
	*/
	void show(bool show) {
		visible = show;
	}
private:
	/**
	 * @brief Whether the ui element is visible.
	*/
	bool visible = true;
};