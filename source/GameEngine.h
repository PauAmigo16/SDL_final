#pragma once
#include <SDL.h>
#include "SceneManager.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Gameplay.h"
#include "RenderManager.h"
#include "TimeManager.h"

#include <random>

class GameEngine
{
private:
	//------ EXECUTION CONTROL
	bool isRunning;

	//------ SDL
	SDL_Window* window;
	SDL_Renderer* renderer;

	int windowWidth;
	int windowHeight;

	void InitSDL();
	//There's an errror trying to create the window on here...
	//void InitWindowAndRenderer(int width, int height);
	

	//----- RENDER
	int RandomNum();
	void Render();
	void FillScenes();



public:
	GameEngine();
	void Init();
	void Run();
	void Quit();
};