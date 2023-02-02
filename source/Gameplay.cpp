#include "Gameplay.h"


Gameplay::Gameplay()
{
	states = GameState::GAMEPLAY;
	level = 1;
	player = new Frog();
	playerFood = false;
	endHazardTimer = TM->GetCurrentTime();
	reachEndTime = 0;
	death = false;
	TimeBar* time = new TimeBar();
	gameUI.emplace("timeBar", time);
	Score* score = new Score();
	gameUI.emplace("score", score);

	Lives* lives = new Lives();
	gameUI.emplace("lives", lives);

	text = new TextRenderer({ 255,255,255 }, 255, 0, { (int)((RM->windowWidht / 8) * 3), (int)(RM->gridY / 4), (int)((RM->windowWidht / 8) * 2), (int)(RM->gridY / 2) }, "Max Score");
	text->Load("resources/myFont.ttf");

	position = RM->gridY * 13;

	lostLive = true;

	UIPanel* gameOver = new UIPanel({
		(int)(RM->windowWidht / 4),
		(int)(RM->windowHeight / 4),
		(int)(RM->windowWidht / 2),
		(int)(RM->windowHeight / 2)
		}, "GAME OVER");

	gameOver->AddButton({
		(int)gameOver->transform.GetPosition().x + ((int)gameOver->transform.GetScale().x / 4),
		(int)gameOver->transform.GetPosition().y + (int)((gameOver->transform.GetScale().y / 4) * 2),
		(int)gameOver->transform.GetScale().x / 2,
		(int)gameOver->transform.GetScale().y / 6
		}, "returnGame", "Reload");

	gameOver->AddButton({
		(int)gameOver->transform.GetPosition().x + ((int)gameOver->transform.GetScale().x / 4),
		(int)gameOver->transform.GetPosition().y + (int)((gameOver->transform.GetScale().y / 4) * 3),
		(int)gameOver->transform.GetScale().x / 2,
		(int)gameOver->transform.GetScale().y / 6
		}, "returnMenu", "Exit");

	gameUI.emplace("gameOver", gameOver);

	UIPanel* pause = new UIPanel({
		(int)(RM->windowWidht / 4),
		(int)(RM->windowHeight / 4),
		(int)(RM->windowWidht / 2),
		(int)(RM->windowHeight / 2)
		}, "Pause");

	pause->AddButton({
		(int)pause->transform.GetPosition().x + ((int)pause->transform.GetScale().x / 4),
		(int)pause->transform.GetPosition().y + (int)((pause->transform.GetScale().y / 4) * 2),
		(int)pause->transform.GetScale().x / 2,
		(int)pause->transform.GetScale().y / 6
		}, "restart", "Restart");

	pause->AddButton({
		(int)pause->transform.GetPosition().x + ((int)pause->transform.GetScale().x / 4),
		(int)pause->transform.GetPosition().y + (int)((pause->transform.GetScale().y / 4) * 3),
		(int)pause->transform.GetScale().x / 2,
		(int)pause->transform.GetScale().y / 6 },
		"exit", "Exit");

	gameUI.emplace("Pause", pause);

}
void Gameplay::LoadLevelFromFile(std::string path)
{
	LevelLoader::LoadLevel(path, this);
}
void Gameplay::SaveScore()
{
}
void Gameplay::Update()
{
	int endPosition = 0;
	bool isWater = false;

	for (auto pos : endPositions)
	{
		if (!pos->frog)
		{
			endPosition++;
		}
	}

	switch (states)
	{
	case Gameplay::GAMEPLAY:

		if (IM->CheckKeyState(SDLK_ESCAPE, PRESSED))
		{
			TM->PauseGame(true);
			AM->ToggleAudio();
			states = GameState::PAUSE;
			break;
		}

		if (currentLevelTime + levelMaxTime < TM->GetCurrentTime())
		{
			player->Respawn();
			if (player->haveFood())
				playerFood = false;

			states = GameState::DEAD;
		}

		if (player->GetTransform().GetPosition().y == position - RM->gridY && !player->IsDead())
		{
			position = player->GetTransform().GetPosition().y;
			dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(10);
		}


		if (endHazardTimer + 4 < TM->GetCurrentTime())
		{
			endHazardTimer = TM->GetCurrentTime();

			fly = false;

			for (auto pos : endPositions)
			{
				if (pos->addFly)
				{
					fly = true;
				}
			}

			int pos = rand() % endPosition;

			while (endPositions[pos]->frog == true)
			{
				pos = (pos + 1) % 5;
			}


			if (rand() % 100 < endHazardChances && !endPositions[pos]->addFly)
			{
				if (endPositions[pos]->addCrocodile == false)
				{
					endPositions[pos]->addCrocodile = true;
					endPositions[pos]->ActiveAnimatios();
				}

			}
			else if (!fly && endPositions[pos]->addCrocodile == false)
			{
				endPositions[pos]->addFly = true;
				endPositions[pos]->ActiveAnimatios();

			}

		}

		for (auto UI : gameUI)
		{
			UI.second->Update();
		}

		for (auto spawns : spawners) {
			if (spawns->Update())
			{
				spawns->GetObject(this);
			}
		}

		for (auto pos : endPositions)
		{
			pos->Update();
		}


		for (int i = 0; i < objects.size(); i++) {

			objects[i]->Update();
			if ((objects[i]->GetTransform().GetPosition().x < -(objects[i]->GetTransform().GetScale().x) || objects[i]->GetTransform().GetPosition().x > RM->windowWidht))
			{
				if (objects[i]->IsFood())
				{
					playerFood = false;
				}

				delete objects[i];
				objects.erase(objects.begin() + i);
				i--;
			}
		}
		player->Update();
		lostLive = true;


		for (int i = 0; i < endPositions.size(); i++)
		{
			if (endPositions[i]->boundingBox.CheckOverlappingAABB(&player->boundingBox))
			{
				if (endPositions[i]->lethal)
				{
					TM->PauseGame(true);
					states = GameState::DEAD;
					player->Respawn();
					if (player->haveFood()) {
						playerFood = false;
					}
				}
				else if (endPositions[i]->addFly)
				{
					if (endPosition != 1)
						AM->PlayClip("EndTile", 0);
					else
						AM->PlayClip("EndLevel", 0);

					dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(dynamic_cast<TimeBar*>(gameUI.find("timeBar")->second)->GetPercentage() * 2);

					restartTime();
					this->position = RM->gridY * 13;

					endPositions[i]->addFly = false;
					endPositions[i]->frog = true;
					if (player->haveFood())
					{
						playerFood = false;
						dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(200);
					}
					else
					{
						dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(100);

					}
					TM->PauseGame(true);
					states = GameState::MAPEND;
					reachEndTime = TM->GetCurrentTimeInPause();

				}
				else
				{
					dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(dynamic_cast<TimeBar*>(gameUI.find("timeBar")->second)->GetPercentage() * 2);

					restartTime();
					this->position = RM->gridY * 13;

					endPositions[i]->frog = true;
					if (player->haveFood())
					{
						playerFood = false;
						dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(100);

					}
					TM->PauseGame(true);
					states = GameState::MAPEND;
					reachEndTime = TM->GetCurrentTimeInPause();

					if (endPosition != 1)
						AM->PlayClip("EndTile", 0);
					else
						AM->PlayClip("EndLevel", 0);
				}
			}
		}

		if (!player->IsMoving() && !player->IsDead())
		{
			bool objectFound = false;

			for (auto object : objects) {
				if (object->boundingBox.CheckOverlappingAABB(&player->boundingBox))
				{
					objectFound = true;

					if (object->lethal)
					{
						if (player->haveFood())
							playerFood = false;

						player->Respawn();
						TM->PauseGame(true);
						states = GameState::DEAD;

					}
					else
					{
						player->velocity = object->velocity;
					}

					if (object->GetObject() != nullptr)
					{
						if (object->GetObject()->boundingBox.CheckOverlappingAABB(&player->boundingBox))
						{
							objectFound = true;
							if (object->GetObject()->lethal)
							{
								if (player->haveFood())
									playerFood = false;
								player->Respawn();
								TM->PauseGame(true);
								states = GameState::DEAD;

							}
							else if (object->GetObject()->IsFood())
							{
								player->AddFood();
								object->deleteFood();

							}
						}
					}
				}
			}

			if (!objectFound)
			{
				player->velocity = { 0,0 };
				for (auto tile : tiles) {

					if (tile->boundingBox.CheckOverlappingAABB(&player->boundingBox))
					{
						if (tile->lethal)
						{
							isWater = dynamic_cast<Tile*>(tile)->IsWater();

							if (player->haveFood())
								playerFood = false;
							player->Respawn();
							TM->PauseGame(true);
							states = GameState::DEAD;

						}
					}
				}
			}
		}

		if (player->IsDead())
		{
			restartTime();
			this->position = RM->gridY * 13;

			if (lostLive)
			{
				dynamic_cast<Lives*>(gameUI.find("lives")->second)->LostLive();
				lostLive = false;


				if (dynamic_cast<Lives*>(gameUI.find("lives")->second)->GetLives() == -1)
				{
					AM->MuteAudio();
					AM->PlayClip("GameOver", 0);

					death = true;
					return;
				}
				else
				{
					if (isWater)
						AM->PlayClip("Water", 0);
					else
						AM->PlayClip("Dead", 0);
				}
			}
		}
		break;
	case Gameplay::PAUSE:
		dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->CheckButtonCollision({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });

		if (dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->CheckIfButtonPresed("restart"))
		{
			TM->PauseGame(false);
			AM->ToggleAudio();
			states = GameState::GAMEPLAY;
			dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->StopPress();
		}
		else if (dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->CheckIfButtonPresed("exit"))
		{
			this->position = RM->gridY * 13;

			player->returnGame();
			TM->PauseGame(false);
			AM->ToggleAudio();

			SM->SetScene("mainMenu");
			states = GameState::GAMEPLAY;
			dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->StopPress();

			death = false;

			dynamic_cast<Lives*>(gameUI.find("lives")->second)->SetLives(3);
			dynamic_cast<Score*>(gameUI.find("score")->second)->SetScore(0);
		}
		break;

	case Gameplay::DEAD:
		player->Update();

		if (death)
		{
			dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->CheckButtonCollision({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });

			if (dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->CheckIfButtonPresed("returnGame"))
			{
				TM->PauseGame(false);
				player->returnGame();
				states = GameState::GAMEPLAY;
				RestartLevel();
				dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->StopPress();
			}

			if (dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->CheckIfButtonPresed("returnMenu"))
			{
				TM->PauseGame(false);

				SM->SetScene("mainMenu");
				states = GameState::GAMEPLAY;

				dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->StopPress();

				death = false;

				dynamic_cast<Lives*>(gameUI.find("lives")->second)->SetLives(3);
				dynamic_cast<Score*>(gameUI.find("score")->second)->SetScore(0);
			}
		}
		else
		{
			if (player->IsDead() == false)
			{
				TM->PauseGame(false);
				states = GameState::GAMEPLAY;
			}
		}
		break;

	case Gameplay::MAPEND:
		if (reachEndTime + 2 < TM->GetCurrentTimeInPause())
		{
			if (endPosition == 0)
			{
				OnExit();

				level += 1;

				OnEnter();
				states = GameState::GAMEPLAY;
			}
			else
			{
				states = GameState::GAMEPLAY;
			}

			TM->PauseGame(false);
			player->end();
		}
		break;
	}
}

void Gameplay::Render()
{
	for (auto tile : tiles)
	{
		tile->Render();
	}
	for (auto object : objects)
	{
		if (object != nullptr)
			object->Render();
	}
	for (auto pos : endPositions)
	{
		pos->Render();
	}
	for (auto UI : gameUI)
	{
		if (UI.first != "gameOver" && UI.first != "Pause")
			UI.second->Render();
	}

	text->Render();

	switch (states)
	{
	case Gameplay::GAMEPLAY:
		player->Render();

		break;
	case Gameplay::PAUSE:
		player->Render();

		dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->Render();

		break;
	case Gameplay::DEAD:
		player->Render();

		if (death)
		{
			dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->Render();
		}
		break;
	}
}

void Gameplay::OnEnter()
{
	AM->PlayMusic("GameplayMusic");

	//TODO put max score here so it prints
	text->SetText("Max Score: ");

	if (level == 1)
	{
		LoadLevelFromFile("res/files/lvl1.xml");
	}
	else if (level == 2)
	{
		LoadLevelFromFile("res/files/lvl2.xml");
	}
	else
	{
		this->position = RM->gridY * 13;

		player->returnGame();
		TM->PauseGame(false);

		SM->SetScene("mainMenu");
		states = GameState::GAMEPLAY;

		death = false;

		dynamic_cast<Lives*>(gameUI.find("lives")->second)->SetLives(3);
		dynamic_cast<Score*>(gameUI.find("score")->second)->SetScore(0);
	}

	restartTime();
}

void Gameplay::OnExit()
{
	for (int i = tiles.size() - 1; i >= 0; i--) {
		delete tiles[i];
	}
	for (auto object : objects) {
		delete object;
	}
	for (auto pos : endPositions)
	{
		delete pos;
	}
	for (auto spawn : spawners)
	{
		delete spawn;
	}
	spawners.resize(0);
	tiles.resize(0);
	objects.resize(0);
	endPositions.resize(0);

	AM->MuteAudio();
}

void Gameplay::SetObject(Object* object)
{
	if (object != nullptr)
		objects.push_back(object);
}

void Gameplay::restartTime()
{
	currentLevelTime = TM->GetCurrentTime();
	dynamic_cast<TimeBar*>(gameUI.find("timeBar")->second)->SetStartTime(TM->GetCurrentTime());
}

void Gameplay::RestartLevel()
{
	death = false;

	OnExit();
	level = 1;
	OnEnter();

	dynamic_cast<Lives*>(gameUI.find("lives")->second)->SetLives(3);
	dynamic_cast<Score*>(gameUI.find("score")->second)->SetScore(0);

	for (auto end : endPositions)
	{
		end->frog = false;
	}
}
