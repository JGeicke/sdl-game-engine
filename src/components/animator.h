#pragma once
#include "basecomponent.h"
#include <map>
#include <vector>
#include "SDL.h"
#include "../util/fileloader.h"
#include "../util/texture.h"
/**
 * @brief Enum of animation states used for different animation.
*/
enum STATES {
	IDLE_SIDE,
	WALK_SIDE,
	IDLE_UP,
	WALK_UP,
	IDLE_DOWN,
	WALK_DOWN,
};

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
		this->currentYOffset = 0;
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
		std::cout << "Animator (Entity: " << entity.uid << ") # of Animations: " << animations.size() << std::endl;
	}

	/**
	 * @brief Default constructor of animator component.
	*/
	Animator() {}

	/**
	 * @brief Adds an animation the the animator component that uses sprite texture for animation.
	 * @param animationState - State to play the animation.
	 * @param frames - Number of frames of the animation.
	 * @param frameDelayMS - Delay between animation frames.
	*/
	void addAnimation(size_t animationState, int frames, int frameDelayMS) {
		Texture t;
		t.emptyInit();
		addAnimation(animationState, frames, frameDelayMS, t);
	}

	/**
	 * @brief Adds an animation the the animator component.
	 * @param animationState - State to play the animation.
	 * @param frames - Number of frames of the animation.
	 * @param frameDelayMS - Delay between animation frames.
	 * @param texture - Texture of the animation.
	*/
	void addAnimation(size_t animationState, int frames, int frameDelayMS, Texture texture) {
		animations.insert(animations.begin()+animationState,*(new Animation(frames, frameDelayMS, texture)));

		// check if current animation is currently not set
		if (currentState == SIZE_MAX) {
			currentState = animationState;
		}
	}
	
	/**
	* @brief Checks if the animator component has animations.
	* @return Whether the animator component has animations.
	*/
	bool hasAnimation() {
		return animations.size() > 0;
	}

	/**
	 * @brief Gets the currently played animation.
	 * @return Current animation. Returns nullptr if no animation is present
	*/
	Animation* getCurrentAnimation() {
		if (currentState < animations.size()) {
			return &animations[currentState];
		}
		return nullptr;
	}

	/**
	 * @brief Gets the current state of the animator.
	 * @return Current state.
	*/
	size_t getState() {
		return currentState;
	}

	/**
	 * @brief Sets the new animation state.
	*/
	void setState(size_t newState) {
		if (newState < animations.size()) {
			animations[currentState].resetYOffset();
			currentState = newState;
		}
	}
private:
	/**
	* @brief Map that maps the name of an animation to the animation struct.
	*/
	//std::map<const char*, Animation*> animations;

	std::vector<Animation> animations = {};

	/**
	* @brief Current state of animator.
	*/
	size_t currentState = SIZE_MAX;
};