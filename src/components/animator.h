#pragma once
#include "basecomponent.h"
#include <map>
#include "SDL.h"
struct Animation {
	int frames;
	int frameDelayMS;

	Animation(int frames, int frameDelayMS) {
		this->frameDelayMS = frameDelayMS;
		this->frames = frames;
		this->incrementFrame = -1;
	}

	void incrementYOffset(int frame) {
		if (frame == incrementFrame) return;
		currentYOffset++;
		incrementFrame = frame;
	}

	void resetYOffset() {
		currentYOffset = 0;
		incrementFrame = -1;
	}

	int getYOffset() {
		return currentYOffset;
	}
private:
	int currentYOffset;
	int incrementFrame;
};

struct Animator : BaseComponent {
public:
	void print() {
		//TODO: implement print for animator
	}

	void addAnimation(const char* animationName, int frames, int frameDelayMS) {
		Animation* tempAnimation = new Animation(frames, frameDelayMS);
		animations[animationName] = tempAnimation;
	}

	void play(const char* animationName) {
		currentAnimation = animationName;
	}

	Animation* getCurrentAnimation() {
		return animations[currentAnimation];
	}

private:
	std::map<const char*, Animation*> animations;
	const char* currentAnimation;
};