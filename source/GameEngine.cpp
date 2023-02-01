#include "GameEngine.h"

GameEngine::GameEngine() {

	isRunning = false;
	lastFrame = 0;
}

#pragma region INITIALIZATION
void GameEngine::Init() {
	//Initialize SDL
	InitSDL();

	TTF_Init();
	//Create a window and a renderer


	Gameplay* gameplay = new Gameplay();
	SplashScreen* splashScreen = new SplashScreen();
	MainMenu* mainMenu = new MainMenu();
	Ranking* ranking = new Ranking();

	
	SM->AddScene("Gameplay", gameplay);
	SM->AddScene("splashScreen", splashScreen);
	SM->AddScene("mainMenu", mainMenu);
	SM->AddScene("ranking", ranking);

	
	SM->SetScene("splashScreen");
}

void GameEngine::InitSDL() {
	int result = SDL_Init(SDL_INIT_VIDEO);

	bool success = result >= 0;
	if (!success)
		throw SDL_GetError();
}





#pragma endregion INITIALIZATION

void GameEngine::Quit() {
	//Para guardar la puntuacion en caso de cerrar el juego en medio del gameplay
	dynamic_cast<Ranking*>(SM->GetScene("ranking"))->SetNewScore(dynamic_cast<Score*>(dynamic_cast<Gameplay*>(SM->GetScene("Gameplay"))->gameUI.find("score")->second)->GetScore());

	RM->Quit();
}



void GameEngine::Run() {
	while (!isRunning && !dynamic_cast<MainMenu*>(SM->GetScene("mainMenu"))->exitGame) {
		//HandleEvents();
		IM->Listen();
		isRunning = IM->GetQuitEvent();

		TM->Update();



		if (TM->GetFrameIncrement() > lastFrame)
		{		

		SM->GetCurrentScene()->Update();


		lastFrame = TM->GetFrameIncrement();
		}			

		//Update();





		//Render();
		Render();

		


	}
}

void GameEngine::Render()
{
	RM->ClearScreen();

	SM->GetCurrentScene()->Render();

	SDL_RenderPresent(RM->GetRenderer());

	RM->RenderScreen();

}
