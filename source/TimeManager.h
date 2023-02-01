#pragma once
#include <SDL.h>
#include <iostream>

#define TM TimeManager::GetInstance()

class TimeManager {
private:
	float deltaTime;
	float lastGameTime;
	float Time;
	static TimeManager* instance;
	TimeManager();
	int frameIncrement;
	float currentFrameTime;
	bool pause;
public:
	static const float FPS;
	static const float TICK;
	static TimeManager* GetInstance();
	void Update();
	float GetCurrentTime();
	float GetDT();
	int GetFrameIncrement();
	void PauseGame(bool pause);
	bool GameState();
	float GetCurrentTimeInPause();

};