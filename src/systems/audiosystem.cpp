#include "audiosystem.h"
/**
* @brief Constructor of the audio system.
* @param audioManager - Audio manager to access the audio components.
*/
AudioSystem::AudioSystem(ComponentManager<Audio>* audioManager) {
	this->audioManager = audioManager;
	this->bgm = nullptr;

	this->masterVolume = .5f;
	this->soundVolume = 1.0f;
	this->musicVolume = 1.0f;
}
/**
* @brief Destructor of the audio system. Frees the allocated space of the bgm.
*/
AudioSystem::~AudioSystem() {
	Mix_FreeMusic(bgm);
}

/**
* @brief Audio system update loop. Iterates the audio components to check if the audio clips should be played.
*/
void AudioSystem::update() {
	size_t componentCount = audioManager->getComponentCount();
	for (size_t i = 0; i < componentCount; i++)
	{
		Audio* audioComponent = audioManager->getComponentWithIndex(i);
		while (audioComponent->getPlayedAudioClipsCount() > 0) {
			AudioClip* nextClip = audioComponent->getNextAudioClip();
			this->playSound(nextClip);
		}
	}
}

/**
* @brief Initializes the audio system.
*/
void AudioSystem::init() {
	// initializes SDL_mixer with frequency of 44100, default sample format, 8 hardware channels and 2048 byte chunk size
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", "Could not initialize SDL Mixer!", NULL);
	}
}

/**
* @brief Adds background music from file.
* @param filePath - Path to file.
*/
void AudioSystem::addBGM(const char* filePath) {
	bgm = Mix_LoadMUS(filePath);
	if (bgm == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Mixer Error", "Could not load background music file!", NULL);
	}
}

/**
* @brief Plays the current background music and adjusts the volume.
* @param loopBGM - Whether bgm should be looped.
*/
void AudioSystem::playBGM(bool loopBGM) {
	if (bgm != nullptr) {
		int loops = 1;

		// check if bgm should be looped
		if (loopBGM) {
			loops = -1;
		}
		Mix_PlayMusic(bgm, loops);
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * (masterVolume * musicVolume)));
	}
}

/**
* @brief Toggles the current background music.
*/
void AudioSystem::toggleBGM() {
	if (bgm != nullptr) {
		if (Mix_PlayingMusic() == 1) {
			// bgm is playing
			Mix_HaltMusic();
		}
		else {
			// bgm is not playing
			Mix_ResumeMusic();
		}
	}
}

/**
* @brief Plays audio clip and adjusts the volume of the audio channel.
* @param audio - Audio clip to be played.
*/
void AudioSystem::playSound(AudioClip* audio) {
	int channel = Mix_PlayChannel(-1, audio->getAudioChunk(), 0);
	Mix_Volume(channel, (int)(MIX_MAX_VOLUME * (masterVolume * soundVolume)));
}