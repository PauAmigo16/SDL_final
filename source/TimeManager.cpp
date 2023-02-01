#include "TimeManager.h"

const float TimeManager::FPS = 140.0f;
const float TimeManager::TICK = 1.0f / 140.0f;

TimeManager* TimeManager::instance = nullptr;


TimeManager::TimeManager()
{
	deltaTime = 0;
	lastGameTime = SDL_GetTicks();
	currentFrameTime = 0;
	Time = 0;
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

	deltaTime = (SDL_GetTicks() - lastGameTime) / 1000;
	lastGameTime = SDL_GetTicks();

	if(!pause)
		Time += deltaTime;

	currentFrameTime += deltaTime;

	frameIncrement = currentFrameTime / TICK;

}

float TimeManager::GetCurrentTime()
{

    return Time;
}

float TimeManager::GetDT()
{
		return TICK;

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

float TimeManager::GetCurrentTimeInPause()
{
	return currentFrameTime;
}
