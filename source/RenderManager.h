#pragma once
#include<SDL.h>

#define RM RenderManager::GetInstance()


class RenderManager {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	static RenderManager* instance;
	RenderManager(int width,int height, int flags);
public:	SDL_Surface* surface;

	float windowWidht;
	float windowHeight;
	static RenderManager* GetInstance();
	SDL_Renderer* GetRenderer();
	void ClearScreen();
	void RenderScreen();
	float gridX;
	float gridY;

	void Quit();





};
