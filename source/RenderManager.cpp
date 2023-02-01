#include "RenderManager.h"


RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager(int width, int height, int flags)
{
	windowWidht = width;
	windowHeight = height;

	int result = SDL_CreateWindowAndRenderer(windowWidht, windowHeight, SDL_WINDOW_RESIZABLE|SDL_WINDOW_SHOWN, &window, &renderer);

	bool success = result >= 0;
	if (!success)
		throw SDL_GetError();
}

RenderManager* RenderManager::GetInstance()
{

	if (instance == nullptr)
	{
		instance = new RenderManager(224*3, 240*3, 0);
		instance->gridX = instance->windowWidht / 14;
		instance->gridY = instance->windowHeight / 15;

	}
	return instance;
}

SDL_Renderer* RenderManager::GetRenderer()
{
	return renderer;
}

void RenderManager::ClearScreen()
{
	SDL_RenderClear(renderer);

}

void RenderManager::RenderScreen()
{
	SDL_RenderPresent(renderer);

}

void RenderManager::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
