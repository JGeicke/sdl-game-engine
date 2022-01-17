#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
/**
 * @brief Audio system to manage the ingame audio.
*/
class AudioSystem : public GameSystem {
public:
	/**
	 * @brief Constructor of the audio system.
	 * @param audioManager - Audio manager to access the audio components.
	*/
	AudioSystem(ComponentManager<Audio>* audioManager);

	/**
	* @brief Destructor of the audio system.
	*/
	~AudioSystem();

	/**
	 * @brief Audio system update loop.
	*/
	virtual void update();

	/**
	 * @brief Initializes the audio system.
	*/
	virtual void init();

	/**
	 * @brief Adds background music from file.
	 * @param filePath - Path to file.
	*/
	void addBGM(const char* filePath);

	/**
	 * @brief Plays the current background music.
	*/
	void playBGM();

	/**
	 * @brief Toggles the current background music.
	*/
	void toggleBGM();

	/**
	 * @brief Plays audio clip.
	 * @param audio - Audio clip to be played.
	*/
	void playSound(AudioClip* audio);

	/**
	 * @brief Sets the master volume of the audio system.
	 * @param newMasterVolume - New master volume.
	*/
	void setMasterVolume(float newMasterVolume) {
		masterVolume = newMasterVolume;
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * (masterVolume * musicVolume)));
	}

	/**
	 * @brief Sets the sound volume of the audio system.
	 * @param newSoundVolume - New sound volume.
	*/
	void setSoundVolume(float newSoundVolume) {
		soundVolume = newSoundVolume;
	}

	/**
	 * @brief Sets the music volume of the audio system.
	 * @param newMusicVolume - New music volume.
	*/
	void setMusicVolume(float newMusicVolume) {
		musicVolume = newMusicVolume;
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * (masterVolume * musicVolume)));
	}

	/**
	 * @brief Gets the current master volume.
	 * @return The current master volume.
	*/
	float getMasterVolume() { return masterVolume; }

	/**
	 * @brief Gets the current music volume.
	 * @return The current music volume.
	*/
	float getMusicVolume() { return musicVolume; }

	/**
	 * @brief Gets the current sound volume.
	 * @return The current sound volume.
	*/
	float getSoundVolume() { return soundVolume; }
private:
	/**
	 * @brief Pointer to the audio manager to access the audio components.
	*/
	ComponentManager<Audio>* audioManager;
	/**
	 * @brief Current background music.
	*/
	Mix_Music* bgm;
	
	/**
	 * @brief Current master volume. Directly affects the volume of every audio.
	*/
	float masterVolume;
	/**
	 * @brief Current sound volume. Directly affects the volume of every audio clip.
	*/
	float soundVolume;

	/**
	 * @brief Current music volume. Directly affects the volume of the background music.
	*/
	float musicVolume;
};