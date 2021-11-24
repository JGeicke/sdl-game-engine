#pragma once
#include "gamesystem.h"
#include "../componentmanager.h"
#include "../components/components.h"
/**
 * @brief Audio system to manage the ingame audio.
*/
class AudioSystem : GameSystem {
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
	}
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