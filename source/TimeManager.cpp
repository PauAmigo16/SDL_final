#include "TimeManager.h"

const float TimeManager::FPS = 140.0f;
const float TimeManager::TICK = 1.0f / 140.0f;

TimeManager* TimeManager::instance = nullptr;


TimeManager::TimeManager()
{
	dt = 0;
	lastGameTime = SDL_GetTicks();
	currentFrameTime = 0;
	eTime = 0;
	pause = false;
}

TimeManager* TimeManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TimeManager();
	}
	return instance;
}

void TimeManager::Update()
{

	dt = (SDL_GetTicks() - lastGameTime) / 1000;
	lastGameTime = SDL_GetTicks();

	if(!pause)
		eTime += dt;

	currentFrameTime += dt;

	frameIncrement = currentFrameTime / TICK;

}

float TimeManager::GetCurrentTime()
{

    return eTime;
}

float TimeManager::GetDT()
{
		return TICK;

}

float TimeManager::GetCurrentTimeInPause()
{
	return currentFrameTime;
}

int TimeManager::GetFrameIncrement()
{

	return frameIncrement;
}

void TimeManager::PauseGame(bool pause)
{
	this->pause = pause;
}

bool TimeManager::GameState()
{
	return pause;
}

