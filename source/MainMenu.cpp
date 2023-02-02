#include "MainMenu.h"

MainMenu::MainMenu()
{
	gameExit = false;
	audioIsOn = true;
	UIButton* game = new UIButton({(int)(RM->windowWidht/4),(int)((RM->windowHeight/15)*2), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Play");
	myButton.emplace("game", game);

	UIButton* exit = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 5), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Exit");
	myButton.emplace("exit", exit);

	UIButton* ranking = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 8), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Ranking");
	myButton.emplace("ranking", ranking);

	UIButton* audio = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 11), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Audio On");
	myButton.emplace("audio", audio);

}

void MainMenu::Update()
{
	for (auto button : myButton)
	{
		button.second->ComproveCollision({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });
	}
	if (myButton.find("game")->second->isPressed)
	{
		SM->SetScene("Gameplay");


		myButton.find("game")->second->isPressed = false;
	}
	else if (myButton.find("exit")->second->isPressed)
	{
		gameExit = true;


		myButton.find("exit")->second->isPressed = false;
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
			AM->SetAudio();
			AM->PlayMusic("MenuMusic");
		}
		else
		{
			myButton.find("audio")->second->SetText("Audio Off");
			AM->SetAudio();

		}

		myButton.find("audio")->second->isPressed = false;
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
	AM->StopAudios();
}
