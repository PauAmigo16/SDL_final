#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != -1);

	LoadSFX("Dead");
	LoadSFX("EndLevel");
	LoadSFX("Jump");
	LoadSFX("LostAllLives");
	LoadSFX("ReachEnd");
	LoadSFX("Water");
	LoadMusic("GameplayMusic");
	LoadMusic("MenuMusic");

	isMuted = false;
}

AudioManager* AudioManager::GetInstance()
{

	if (instance == nullptr)
	{
		instance = new AudioManager;
	}
	return instance;
}

void AudioManager::LoadSFX(std::string audioName)
{
	assert(sfx.find(audioName) == sfx.end());

	Mix_Chunk* loadedChunk = Mix_LoadWAV(("resources/Audio/" + audioName + ".wav").c_str());

	assert(loadedChunk != nullptr);

	sfx.emplace(audioName, loadedChunk);
}

void AudioManager::UnLoadSFX(std::string audioName)
{
}

void AudioManager::LoadMusic(std::string audioName)
{
	assert(music.find(audioName) == music.end());

	Mix_Music* loadedMusic = Mix_LoadMUS(("resources/Audio/" + audioName + ".wav").c_str());

	assert(loadedMusic != nullptr);

	music.emplace(audioName, loadedMusic);
}

void AudioManager::UnLoadMusic(std::string audioName)
{
}

void AudioManager::PlaySFX(std::string audioName, int repeticions)
{
	assert(sfx.find(audioName) != sfx.end());



	if (!isMuted)
	Mix_PlayChannel(1, sfx[audioName], repeticions);

}

void AudioManager::PlayMusic(std::string audioName)
{
	assert(music.find(audioName) != music.end());



	if (!isMuted)
	Mix_FadeInMusic(music[audioName], -1, 200);
}

void AudioManager::StopAudios()
{
	Mix_CloseAudio();
	assert(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != -1);

}



void AudioManager::SetAudio()
{
	isMuted = !isMuted;
	if (isMuted) {
		Mix_Pause(-1);
		Mix_PauseMusic();
	}
	else {
		Mix_Resume(-1);
		Mix_ResumeMusic();
	}

}

