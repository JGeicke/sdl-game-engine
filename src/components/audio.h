#pragma once
#include "basecomponent.h"
#include "SDL.h"
#include "SDL_mixer.h"
struct AudioClip{
public:
	AudioClip(){}

	AudioClip(const char* filePath) {
		audioChunk = Mix_LoadWAV(filePath);
		if (audioChunk == NULL) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", "Could not load sound file!", NULL);
		}
	}

	~AudioClip() {
		Mix_FreeChunk(audioChunk);
	}

	Mix_Chunk* getAudioChunk() {
		return audioChunk;
	}

	bool play;
private:
	Mix_Chunk* audioChunk = NULL;
};

struct Audio : BaseComponent {
public:
	void print() {
		//TODO: implement audio component
	}

	Audio() {

	}

	void init() {
		currentIndex = 0;
		playedAudioClips = 0;
	}

	size_t addAudioClip(const char* filePath) {
		audioClips[currentIndex] = *(new AudioClip(filePath));
		return currentIndex++;
	}

	AudioClip* getAudioClip(size_t index) {
		if (index < currentIndex) {
			return &audioClips[index];
		}
	}

	void playAudioClip(size_t index) {
		if (index < currentIndex) {
			audioClips[index].play = true;
			playedAudioClips++;
		}
	}

	AudioClip* getNextAudioClip() {
		for (size_t i = 0; i < currentIndex; i++) {
			if (audioClips[i].play) {
				playedAudioClips--;
				audioClips[i].play = false;
				return &audioClips[i];
			}
		}
	}

	unsigned int getPlayedAudioClipsCount() {
		return playedAudioClips;
	}
private:
	AudioClip audioClips[32];
	size_t currentIndex;
	unsigned int playedAudioClips;
};