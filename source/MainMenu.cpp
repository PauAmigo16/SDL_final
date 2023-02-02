#include "MainMenu.h"

MainMenu::MainMenu()
{
	gameExit = false;
	audioIsOn = true;
	//We create the buttons
	UIButton* game;
	UIButton* audio;
	UIButton* ranking;
	UIButton* exit;


	game = new UIButton({(int)(RM->windowWidht/4),(int)((RM->windowHeight/15)*2), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 9) * 2) }, "Play");
	myButton.emplace("game", game);

	audio = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 5), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 9) * 2) }, "Audio On");
	myButton.emplace("audio", audio);
	
	ranking = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 8), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 9) * 2) }, "Ranking");
	myButton.emplace("ranking", ranking);

	exit = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 11), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 9) * 2) }, "Exit");
	myButton.emplace("exit", exit);
}

void MainMenu::Update()
{
	for (auto button : myButton)
	{
		button.second->CheckCollision({(float)IM->GetMouseX(),(float)IM->GetMouseY() });
	}
	if (myButton.find("game")->second->isPressed)
	{
		//Initialize the game
		SM->SetScene("Gameplay");
		myButton.find("game")->second->isPressed = false;
	}
	else if (myButton.find("ranking")->second->isPressed)
	{
		//TODO set scene to ranking
	}
	else if (myButton.find("audio")->second->isPressed)
	{
		audioIsOn = !audioIsOn;
		if (audioIsOn)
		{
			myButton.find("audio")->second->SetText("Audio On");
			AM->ToggleAudio();
			AM->PlayMusic("MenuMusic");
		}
		else
		{
			myButton.find("audio")->second->SetText("Audio Off");
			AM->ToggleAudio();
		}

		myButton.find("audio")->second->isPressed = false;
	}
	else if (myButton.find("exit")->second->isPressed)
	{
		gameExit = true;
		myButton.find("exit")->second->isPressed = false;
	}
}

void MainMenu::Render()
{
	for (auto button : myButton)
	{
		button.second->Render();
	}
}

void MainMenu::OnEnter()
{
	AM->PlayMusic("MenuMusic");
}

void MainMenu::OnExit()
{
	AM->MuteAudio();
}
