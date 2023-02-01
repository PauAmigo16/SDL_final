#pragma once
#include <SDL_mixer.h>
#include <unordered_map>
#include <iostream>
#include <cassert>

#define AM AudioManager::GetInstance()

class AudioManager
{
private:
	std::unordered_map<std::string, Mix_Chunk*> sfx;
	std::unordered_map<std::string, Mix_Music*> music;

	bool isMuted;

	static AudioManager* instance;
	AudioManager();
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
public:
	static AudioManager* GetInstance();

	void LoadSFX(std::string audioName);
	void UnLoadSFX(std::string audioName);

	void LoadMusic(std::string audioName);
	void UnLoadMusic(std::string audioName);

	void PlaySFX(std::string audioName, int repeticions);
	void PlayMusic(std::string audioName);

	void StopAudios();

	void SetAudio();
};