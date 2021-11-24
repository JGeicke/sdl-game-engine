#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
class AudioSystem : GameSystem {
public:
	AudioSystem(ComponentManager<Audio>* audioManager);

	~AudioSystem();

	virtual void update();

	virtual void init();

	void addBGM(const char* filePath);

	void playBGM();

	void playSound(AudioClip* audio);

	void setMasterVolume(float newMasterVolume) {
		masterVolume = newMasterVolume;
	}

	void setSoundVolume(float newSoundVolume) {
		soundVolume = newSoundVolume;
	}
	void setMusicVolume(float newMusicVolume) {
		musicVolume = newMusicVolume;
	}
private:
	SDL_AudioDeviceID audioDeviceId;
	ComponentManager<Audio>* audioManager;
	Mix_Music* bgm;
	
	float masterVolume;
	float soundVolume;
	float musicVolume;
};