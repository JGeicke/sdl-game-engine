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
	ATK_SIDE,
	ATK_DOWN,
	ATK_UP
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
	 * @brief Whether the animation is interruptible.
	*/
	bool interruptible;

	/**
	 * @brief Frame frame count the animation is played in.
	*/
	int currentFrame;

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
		this->interruptible = true;
		this->currentFrame = 0;
	}

	Animation() {
		this->frameDelayMS = 0;
		this->frames = 0;
		this->incrementFrame = -1;
		this->currentYOffset = 0;
		animationTexture = *(new Texture());
		animationTexture.emptyInit();
		this->interruptible = true;
		this->currentFrame = 0;
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

	/**
	 * @brief Checks if the animation is finished.
	 * @return Whether the animation is finished.
	*/
	bool isFinished() {
		return isAnimationFinished;
	}

	/**
	 * @brief Sets the animation to finished.
	*/
	void setFinished() {
		this->isAnimationFinished = true;
	}

	/**
	 * @brief Resets the animation.
	*/
	void resetAnimation() {
		this->isAnimationFinished = false;
		this->currentFrame = 0;
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

	/**
	 * @brief Whether the animation is finshed.
	*/
	bool isAnimationFinished = false;
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
		Texture* t = new Texture();
		t->emptyInit();
		addAnimation(animationState, frames, frameDelayMS, *t);
	}

	/**
	 * @brief Adds an animation the the animator component.
	 * @param animationState - State to play the animation.
	 * @param frames - Number of frames of the animation.
	 * @param frameDelayMS - Delay between animation frames.
	 * @param texture - Texture of the animation.
	*/
	void addAnimation(size_t animationState, int frames, int frameDelayMS, Texture texture) {
		animations[animationState] = *(new Animation(frames, frameDelayMS, texture));
		//animations.insert(animations.begin()+animationState,*(new Animation(frames, frameDelayMS, texture)));

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

	/**
	* @brief Marks an animation as interruptible.
	*/
	void markAnimationInterruptible(size_t state) {
		if (state < animations.size()) {
			animations[state].interruptible = !animations[state].interruptible;
		}
	}
private:
	/**
	* @brief Array that uses the animation state as the index for the animation struct.
	*/
	std::array<Animation,ATK_UP+1> animations = {};

	/**
	* @brief Current state of animator.
	*/
	size_t currentState = SIZE_MAX;
};