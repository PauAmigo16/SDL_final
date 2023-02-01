#pragma once
#include<SDL.h>
#include <cassert>

#define RM RenderManager::GetInstance()

class RenderManager {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	static RenderManager* instance;

	RenderManager(int width,int height);

public:	
	SDL_Surface* surface;

	static RenderManager* GetInstance();

	float windowWidht;
	float windowHeight;

	SDL_Renderer* GetRenderer();

	void ClearScreen();
	void RenderScreen();

	float gridX;
	float gridY;

	void Quit();
};
