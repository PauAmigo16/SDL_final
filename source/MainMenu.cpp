#include "MainMenu.h"

MainMenu::MainMenu()
{
	exitGame = false;
	audioOn = true;
	UIButton* game = new UIButton({(int)(RM->windowWidht/4),(int)((RM->windowHeight/15)*2), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Play");
	buttons.emplace("game", game);

	UIButton* exit = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 5), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Exit");
	buttons.emplace("exit", exit);

	UIButton* ranking = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 8), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Ranking");
	buttons.emplace("ranking", ranking);

	UIButton* audio = new UIButton({ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 15) * 11), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2) }, "Audio On");
	buttons.emplace("audio", audio);

}

void MainMenu::Update()
{
	for (auto button : buttons)
	{
		button.second->ComproveCollision({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });


	}

	if (buttons.find("game")->second->Pressed)
	{
		SM->SetScene("Gameplay");


		buttons.find("game")->second->Pressed = false;
	}
	else if (buttons.find("exit")->second->Pressed)
	{
		exitGame = true;


		buttons.find("exit")->second->Pressed = false;
	}
	else if (buttons.find("ranking")->second->Pressed)
	{
		SM->SetScene("ranking");


		buttons.find("ranking")->second->Pressed = false;
	}
	else if (buttons.find("audio")->second->Pressed)
	{

		audioOn = !audioOn;
		if (!audioOn)
		{
			buttons.find("audio")->second->SetText("Audio Off");
			AM->SetAudio();

		}
		else
		{
			buttons.find("audio")->second->SetText("Audio On");
			AM->SetAudio();
			AM->PlayMusic("MenuMusic");

		}

		buttons.find("audio")->second->Pressed = false;
	}
}

void MainMenu::Render()
{
	for (auto button : buttons)
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
