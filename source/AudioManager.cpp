#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != -1);

	LoadClip("Dead");
	LoadClip("EndLevel");
	LoadClip("Jump");
	LoadClip("LostAllLives");
	LoadClip("ReachEnd");
	LoadClip("Water");
	LoadMusic("GameplayMusic");
	LoadMusic("MenuMusic");

	muted = false;
}

AudioManager* AudioManager::GetInstance()
{
	if (instance == nullptr)
		instance = new AudioManager;
	
	return instance;
}

void AudioManager::LoadClip(std::string audioName)
{
	assert(clips.find(audioName) == clips.end());

	Mix_Chunk* loadedChunk = Mix_LoadWAV(("resources/Audio/" + audioName + ".wav").c_str());

	assert(loadedChunk != nullptr);

	clips.emplace(audioName, loadedChunk);
}

void AudioManager::LoadMusic(std::string audioName)
{
	assert(music.find(audioName) == music.end());

	Mix_Music* loadedMusic = Mix_LoadMUS(("resources/Audio/" + audioName + ".wav").c_str());

	assert(loadedMusic != nullptr);

	music.emplace(audioName, loadedMusic);
}

void AudioManager::PlayClip(std::string audioName, int times)
{
	assert(clips.find(audioName) != clips.end());

	if (!muted)
	Mix_PlayChannel(1, clips[audioName], times);
}

void AudioManager::PlayMusic(std::string audioName)
{
	assert(music.find(audioName) != music.end());

	if (!muted)
	Mix_FadeInMusic(music[audioName], -1, 200);
}

void AudioManager::StopAudios()
{
	Mix_CloseAudio();
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != -1);
}

void AudioManager::SetAudio()
{
	muted = !muted;
	if (muted) {
		Mix_Pause(-1);
		Mix_PauseMusic();
	}
	else {
		Mix_Resume(-1);
		Mix_ResumeMusic();
	}
}

