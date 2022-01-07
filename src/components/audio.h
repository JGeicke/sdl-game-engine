#pragma once
#include "basecomponent.h"
#include "SDL.h"
#include "SDL_mixer.h"
/**
 * @brief Struct to represent playable soundeffect
*/
struct AudioClip{
public:
	/**
	 * @brief Default audio clip constructor.
	*/
	AudioClip(){
		playCount = 0;
	}

	/**
	 * @brief Creates new audio clip from audio file.
	 * @param filePath - Path to audio file.
	*/
	AudioClip(const char* filePath) {
		audioChunk = Mix_LoadWAV(filePath);
		if (audioChunk == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", "Could not load sound file!", NULL);
		}
		playCount = 0;
	}

	/**
	* @brief AudioClip destructor that frees the allocated audio chunk.
	*/
	~AudioClip() {
		if (audioChunk != NULL) {
			Mix_FreeChunk(audioChunk);
		}
	}

	/**
	 * @brief Gets the playable audio chunk.
	 * @return The audio chunk.
	*/
	Mix_Chunk* getAudioChunk() {
		return audioChunk;
	}

	/**
	 * @brief How many times the audio clip should be played.
	*/
	size_t playCount;
private:
	/**
	 * @brief Audio chunk of an audio file.
	*/
	Mix_Chunk* audioChunk = NULL;
};

/**
 * @brief Component to hold audio related data of an entity.
 */
struct Audio : BaseComponent {
public:
	/**
	 * @brief Prints the audio component.
	*/
	void print() {
		std::cout << "Audio (Entity: " << entity.uid << ") # of Audio Clips: " << currentIndex << std::endl;
	}

	/**
	 * @brief Adds an audio clip to the audio component.
	 * @param filePath - Path to audio file to create the audioclip from.
	 * @return Index of the audio clip.
	*/
	size_t addAudioClip(const char* filePath) {
		audioClips[currentIndex] = *(new AudioClip(filePath));
		return currentIndex++;
	}

	/**
	 * @brief Gets the audio clip.
	 * @param index - Index of the audio clip.
	 * @return The audio clip.
	*/
	AudioClip* getAudioClip(size_t index) {
		if (index < currentIndex) {
			return &audioClips[index];
		}
	}

	/**
	 * @brief Marks the audio clip to be played by the audio system.
	 * @param index - Index of the audio clip to mark.
	*/
	void playAudioClip(size_t index) {
		if (index < currentIndex) {
			audioClips[index].playCount += 1;
			playedAudioClips++;
		}
	}

	/**
	 * @brief Gets next audio clip that is marked as played.
	 * @return The marked audio clip. Returns nullptr if no audio clip should be played.
	*/
	AudioClip* getNextAudioClip() {
		for (size_t i = 0; i < currentIndex; i++) {
			if (audioClips[i].playCount > 0) {
				playedAudioClips--;
				audioClips[i].playCount -= 1;
				return &audioClips[i];
			}
		}
		return nullptr;
	}

	/**
	 * @brief Gets the current count of audio clips that should be played by the audio system.
	 * @return Count of marked audio clips.
	*/
	unsigned int getPlayedAudioClipsCount() {
		return playedAudioClips;
	}
private:
	/**
	 * @brief Array of the audio clips.
	*/
	AudioClip audioClips[32];
	/**
	 * @brief Next free index in the array.
	*/
	size_t currentIndex = 0;
	/**
	 * @brief Count of marked audio clips.
	*/
	unsigned int playedAudioClips = 0;
};