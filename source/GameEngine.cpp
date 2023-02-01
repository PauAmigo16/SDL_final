#include "GameEngine.h"

GameEngine::GameEngine(){

	isRunning = false;
	lastFR = 0;
}

#pragma region INITIALIZATION
void GameEngine::Init() {
	//Initialize SDL
	InitSDL();

	//Create a window and a renderer
	
	
	//Initialize the font
	TTF_Init();


	//Initialize the scenes created
	FillScenes();

}

void GameEngine::InitSDL() {
	int result = SDL_Init(SDL_INIT_VIDEO);
	
srand(time(NULL));

	bool success = result >= 0;
	if (!success)
		throw SDL_GetError();
}



#pragma endregion INITIALIZATION

void GameEngine::Quit() {
	//TODO save score
	SDL_DestroyRenderer(renderers);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//RM->Quit();
}



void GameEngine::Run() {
	while (!isRunning && !dynamic_cast<MainMenu*>(SM->GetScene("mainMenu"))->exitGame) {
		//HandleEvents();
		IM->Listen();
		isRunning = IM->GetQuitEvent();

		TM->Update();

		if (TM->GetFrameIncrement() > lastFR)
		{		

			SM->GetCurrentScene()->Update();
			lastFR = TM->GetFrameIncrement();
		}			

		Render();
	}
}

void GameEngine::FillScenes()
{
	
	SM->AddScene("Gameplay", new Gameplay());
	SM->AddScene("splashScreen", new SplashScreen());
	SM->AddScene("mainMenu", new MainMenu());
	//TODO add ranking
	//SM->AddScene("ranking", );
	//Set the first scene
	SM->SetScene("splashScreen");
}


void GameEngine::Render()
{

	RM->ClearScreen();
	SM->GetCurrentScene()->Render();
	SDL_RenderPresent(RM->GetRenderer());
	RM->RenderScreen();

}
