#pragma once
#include <SDL_mixer.h>
#include <unordered_map>
#include <iostream>
#include <cassert>

#define AM AudioManager::GetInstance()

class AudioManager
{
private:
	std::unordered_map<std::string, Mix_Chunk*> clips;
	std::unordered_map<std::string, Mix_Music*> music;

	bool muted;

	static AudioManager* instance;

	AudioManager();

public:
	static AudioManager* GetInstance();

	void LoadClip(std::string audioName);
	void PlayClip(std::string audioName, int times);

	void LoadMusic(std::string audioName);
	void PlayMusic(std::string audioName);

	void MuteAudio();

	void ToggleAudio();
};