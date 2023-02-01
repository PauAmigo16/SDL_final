#pragma once
#include <SDL.h>
#include "SceneManager.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "Ranking.h"
#include "RenderManager.h"
#include "TimeManager.h"

#include <random>

class GameEngine
{
private:
	bool isRunning;

	void InitSDL();
	int lastFrame;
	void Render();
public:
	GameEngine();
	void Init();
	void Run();
	void Quit();
};