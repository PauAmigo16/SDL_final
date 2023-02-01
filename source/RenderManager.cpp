#include "RenderManager.h"


RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager(int width, int height)
{
	windowWidht = width;
	windowHeight = height;

	int result = SDL_CreateWindowAndRenderer(windowWidht, windowHeight,SDL_WINDOW_SHOWN, &window, &renderers);

	bool success = result >= 0;
	assert(success);
}

RenderManager* RenderManager::GetInstance()
{

	if (instance == nullptr)
	{
		instance = new RenderManager(224*3, 240*3);
		instance->gridX = instance->windowWidht / 14;
		instance->gridY = instance->windowHeight / 15;

	}
	return instance;
}

SDL_Renderer* RenderManager::GetRenderer()
{
	return renderers;
}

void RenderManager::ClearScreen()
{
	SDL_RenderClear(renderers);

}

void RenderManager::RenderScreen()
{
	SDL_RenderPresent(renderers);

}

void RenderManager::Quit()
{
	SDL_DestroyRenderer(renderers);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
