#include "RenderManager.h"


RenderManager* RenderManager::instance = nullptr;

RenderManager::RenderManager(int width, int height) : windowHeight(height), windowWidht(width)
{
	int result = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer);

	bool success = result >= 0;
	assert(success);
}

//RenderManager* RenderManager::GetInstance()
//{
//
//	if (instance == nullptr)
//	{
//		instance = new RenderManager(224*3, 240*3, 0);
//		instance->gridX = instance->windowWidht / 14;
//		instance->gridY = instance->windowHeight / 15;
//
//	}
//	return instance;
//}

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
