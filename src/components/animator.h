#pragma once
#include "basecomponent.h"
#include <map>
#include "SDL.h"
#include "../util/fileloader.h"
#include "../util/texture.h"
/**
 * @brief Struct to represent the animation data.
*/
struct Animation {
	/**
	 * @brief Number of frames in the animation.
	*/
	int frames;

	/**
	 * @brief Delay between the frames. Determines the speed of the animation.
	*/
	int frameDelayMS;

	/**
	 * @brief Creates new animation.
	 * @param frames - Number of frames in the animation.
	 * @param frameDelayMS - Delay between frames in animation in milliseconds.
	 * @param texture - Pointer to texture object.
	*/
	Animation(int frames, int frameDelayMS, Texture texture) {
		this->frameDelayMS = frameDelayMS;
		this->frames = frames;
		this->incrementFrame = -1;

		animationTexture = texture;
	}

	/**
	 * @brief Increments the y offset of the animation. Enables different structured tilesets to be used.
	 * @param frame - Frame where the y offset was increased.
	*/
	void incrementYOffset(int frame) {
		if (frame == incrementFrame) return;
		currentYOffset++;
		incrementFrame = frame;
	}

	/**
	 * @brief Resets current y offset.
	*/
	void resetYOffset() {
		currentYOffset = 0;
		incrementFrame = -1;
	}

	/**
	 * @brief Get current y offset.
	 * @return Current y offset.
	*/
	int getYOffset() {
		return currentYOffset;
	}

	/**
	 * @brief Checks if the animation has own texture or uses the sprite texture for animation.
	 * @return If the animation has own texture.
	*/
	bool hasAnimationTexture() {
		return animationTexture.texture;
	}

	/**
	 * @brief Gets pointer to the texture of the animation.
	 * @return Pointer to the texture of the animation.
	*/
	Texture getAnimationTexture() {
		return animationTexture;
	}
private:
	/**
	 * @brief Texture of the animation.
	*/
	Texture animationTexture;

	/**
	 * @brief Current y offset of animation.
	*/
	int currentYOffset;

	/**
	 * @brief Last frame where y offset was incremented.
	*/
	int incrementFrame;
};

/**
* @brief Component to hold data to animate the sprite of the entity.
*/
struct Animator : BaseComponent {
public:
	/**
	 * @brief Prints the animator component.
	*/
	void print() {
		//TODO: implement print for animator
	}

	/**
	 * @brief Adds an animation the the animator component that uses sprite texture for animation.
	 * @param animationName - Name of the animation.
	 * @param frames - Number of frames of the animation.
	 * @param frameDelayMS - Delay between animation frames.
	*/
	void addAnimation(const char* animationName, int frames, int frameDelayMS) {
		Texture t;
		t.emptyInit();
		addAnimation(animationName, frames, frameDelayMS, t);
	}

	/**
	 * @brief Adds an animation the the animator component.
	 * @param animationName - Name of the animation.
	 * @param frames - Number of frames of the animation.
	 * @param frameDelayMS - Delay between animation frames.
	 * @param texture - Texture of the animation.
	*/
	void addAnimation(const char* animationName, int frames, int frameDelayMS, Texture texture) {
		Animation* animation;
		animation = new Animation(frames, frameDelayMS, texture);
		animations[animationName] = animation;
	}

	/**
	 * @brief Play animation with certain name.
	 * @param animationName - Name of animation to play.
	*/
	void play(const char* animationName) {
		currentAnimation = animationName;
	}

	/**
	 * @brief Gets the currently played animation.
	 * @return Current animation.
	*/
	Animation* getCurrentAnimation() {
		return animations[currentAnimation];
	}

private:
	/**
	* @brief Map that maps the name of an animation to the animation struct.
	*/
	std::map<const char*, Animation*> animations;
	/**
	* @brief Name of the currently played animation.
	*/
	const char* currentAnimation;
};