#pragma once
#include <SDL.h>
#include <iostream>

#define TM TimeManager::GetInstance()

class TimeManager {
private:
	static TimeManager* instance;

	float dt;
	float lastGameTime;
	float eTime;
	float currentFrameTime;

	int frameIncrement;

	bool pause;

	TimeManager();

public:

	static const float FPS;//140.0f
	static const float TICK;//1.0f / 140.f

	static TimeManager* GetInstance();

	void Update();

	float GetCurrentTime();
	float GetDT();
	float GetCurrentTimeInPause();

	int GetFrameIncrement();

	void PauseGame(bool pause);

	bool GameState();
};