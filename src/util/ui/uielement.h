#pragma once
struct UIElement {
public:
	bool isVisible() {
		return visible;
	}

	void show(bool showPanel) {
		visible = showPanel;
	}
private:
	bool visible = true;
};