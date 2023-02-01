#include "Gameplay.h"


Gameplay::Gameplay()
{
	states = States::GAMEPLAY;
	level = 1;
	player = new Frog();
	food = false;
	endHazardTimer = TM->GetCurrentTime();
	reachEndTime = 0;
	death = false;
	TimeBar* time = new TimeBar();
	gameUI.emplace("timeBar", time);
	Score* score = new Score();
	gameUI.emplace("score", score);

	Lives* lives = new Lives();
	gameUI.emplace("lives", lives);

	text = new TextRenderer({ 255,255,255 }, 255, 0, { (int)((RM->windowWidht/8)*3), (int)(RM->gridY / 4), (int)((RM->windowWidht / 8) * 2), (int)(RM->gridY/2) }, "Max Score");
	text->Load("resources/pixelart.ttf");


	position = RM->gridY*13;

	lostLive = true;

	UIPanel* gameOver = new UIPanel({
		(int)(RM->windowWidht/4),
		(int)(RM->windowHeight/4),
		(int)(RM->windowWidht/2),
		(int)(RM->windowHeight/2) 
		}, "Reload Game?");

	gameOver->AddButton({ 
		(int)gameOver->transform.GetPosition().x+((int)gameOver->transform.GetScale().x/4),
		(int)gameOver->transform.GetPosition().y+(int)((gameOver->transform.GetScale().y/4)*2),
		(int)gameOver->transform.GetScale().x/2, 
		(int)gameOver->transform.GetScale().y/6 
		}, "returnGame", "Yes");

	gameOver->AddButton({ 
		(int)gameOver->transform.GetPosition().x + ((int)gameOver->transform.GetScale().x/4),
		(int)gameOver->transform.GetPosition().y + (int)((gameOver->transform.GetScale().y/4)*3),
		(int)gameOver->transform.GetScale().x/2, 
		(int)gameOver->transform.GetScale().y/6 
		}, "returnMenu", "No");

	gameUI.emplace("gameOver", gameOver);

	UIPanel* pause = new UIPanel({ 
		(int)(RM->windowWidht/4),
		(int)(RM->windowHeight/4),
		(int)(RM->windowWidht/2),
		(int)(RM->windowHeight/2)
		}, "Pause");

	pause->AddButton({ 
		(int)pause->transform.GetPosition().x + ((int)pause->transform.GetScale().x/4),
		(int)pause->transform.GetPosition().y + (int)((pause->transform.GetScale().y/4)*2),
		(int)pause->transform.GetScale().x/2, 
		(int)pause->transform.GetScale().y/6 
		}, "restart", "Restart");

	pause->AddButton({ 
		(int)pause->transform.GetPosition().x + ((int)pause->transform.GetScale().x/4),
		(int)pause->transform.GetPosition().y + (int)((pause->transform.GetScale().y/4)*3),
		(int)pause->transform.GetScale().x/2, 
		(int)pause->transform.GetScale().y/6 }, 
		"exit", "Exit");

	gameUI.emplace("Pause", pause);

}



void Gameplay::SaveScore()
{
}

void Gameplay::LoadLevelFromFile(std::string path)
{
	LevelLoader::LoadLevel(path,this);
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

		if (IM->CheckKeyState(SDLK_p, PRESSED))
		{
			TM->PauseGame(true);
			states = States::PAUSE;
			break;
		}

		if (player->GetTransform().GetPosition().y == position - RM->gridY && !player->IsDead())
		{
			position = player->GetTransform().GetPosition().y;
			dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(10);
		}
	
		if (currentLevelTime + levelMaxTime < TM->GetCurrentTime())
		{
			player->Respawn();
			if (player->haveFood())
				food = false;

			states = States::DEATH;

		}

		for (auto UI : gameUI)
		{
			UI.second->Update();
		}


		//Cada 4 segundos enviar un evento a una posicion aleatoria del final
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
			else if(!fly&& endPositions[pos]->addCrocodile == false)
			{
				endPositions[pos]->addFly = true;
				endPositions[pos]->ActiveAnimatios();

			}
	
		}


		//Actualizar las posiciones del final para spawnear una mosca o un cocodrilo
		for (auto pos : endPositions)
		{
			pos->Update();
		}


	
		for (auto spawns : spawners) {

			//Comprobar si toca spawnear un objeto
			if (spawns->Update())
			{
			spawns->GetObject(this);
			}


		}

		//Comprobar si el objeto a salido de pantalla
		for (int i = 0; i < objects.size();i++) {

			objects[i]->Update();
			if ((objects[i]->GetTransform().GetPosition().x < -(objects[i]->GetTransform().GetScale().x) || objects[i]->GetTransform().GetPosition().x > RM->windowWidht))
			{
				//Si el objeto tenia comida, actualizar la escena para que sepa que no hay comida en pantalla y pueda spawnear una
				if (objects[i]->GetFood())
				{
					food = false;
				}

				delete objects[i];
				objects.erase(objects.begin() + i);
				i--;

			}

		}	
		player->Update();


			lostLive = true;

			for (int i = 0; i < endPositions.size();i++)
					{
						if (endPositions[i]->boundingBox.CheckOverlappingAABB(&player->boundingBox))
						{
							if (endPositions[i]->getDamage)
							{
								TM->PauseGame(true);
								states = States::DEATH;
								player->Respawn();
								if (player->haveFood())
									food = false;
							}
							else if (endPositions[i]->addFly)
							{
								if (endPosition != 1)
									AM->PlaySFX("ReachEnd", 0);
								else
									AM->PlaySFX("EndLevel", 0);

								dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(dynamic_cast<TimeBar*>(gameUI.find("timeBar")->second)->GetPerc()*2);

								restartTime();
								this->position = RM->gridY * 13;

								endPositions[i]->addFly = false;
								endPositions[i]->frog = true;
								if (player->haveFood())
								{
									food = false;
									dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(200);
									player->addScoreObtainedImage(true, endPositions[i]->transform.GetPosition());

								}
								else
								{
									dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(100);
									player->addScoreObtainedImage(false, endPositions[i]->transform.GetPosition());

								}
								TM->PauseGame(true);
								states = States::REACHEND;
								reachEndTime = TM->GetCurrentTimeInPause();

							}
							else
							{		
								dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(dynamic_cast<TimeBar*>(gameUI.find("timeBar")->second)->GetPerc() * 2);

								restartTime();
								this->position = RM->gridY * 13;

								endPositions[i]->frog = true;
								if (player->haveFood())
								{
									food = false;
									dynamic_cast<Score*>(gameUI.find("score")->second)->AddScore(100);
									player->addScoreObtainedImage(false, endPositions[i]->transform.GetPosition());

								}
								TM->PauseGame(true);
								states = States::REACHEND;
								reachEndTime = TM->GetCurrentTimeInPause();

								if (endPosition != 1)
									AM->PlaySFX("ReachEnd", 0);
								else
									AM->PlaySFX("EndLevel", 0);
							}
						}
					}




		//Comprobar collision del player con el resto de objetos y tiles cuando no se esta moviendo ni esta muerto
		if (!player->IsMoving() && !player->IsDead())
		{
		

			bool objectFound = false;
			for (auto object : objects) {
				if (object->boundingBox.CheckOverlappingAABB(&player->boundingBox))
				{

					objectFound = true;
					if (object->getDamage)
					{
						if (player->haveFood())
							food = false;
						player->Respawn();
						TM->PauseGame(true);
						states = States::DEATH;

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
							if (object->GetObject()->getDamage)
							{			
								if (player->haveFood())
									food = false;
								player->Respawn();
								TM->PauseGame(true);
								states = States::DEATH;

							}
							else if (object->GetObject()->GetFood())
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

						if (tile->getDamage)
						{
							isWater = dynamic_cast<Tile*>(tile)->IsWater();



							if (player->haveFood())
								food = false;
							player->Respawn();
							TM->PauseGame(true);
							states = States::DEATH;

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
					AM->PlaySFX("LostAllLives", 0);

					death = true;
					return;
				}
				else
				{
					if(isWater)
						AM->PlaySFX("Water", 0);
					else
						AM->PlaySFX("Dead", 0);
				}
			}
		}
		break;
	case Gameplay::PAUSE:


		dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->ComproveButtonCol({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });

		if (dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->ComproveIfButtonPresed("restart"))
		{
			TM->PauseGame(false);
			dynamic_cast<Ranking*>(SM->GetScene("ranking"))->SetNewScore(dynamic_cast<Score*>(gameUI.find("score")->second)->GetScore());
			states = States::GAMEPLAY;
			dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->StopPress();
		}
		else if (dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->ComproveIfButtonPresed("exit"))
		{
			this->position = RM->gridY * 13;

			player->returnGame();
			TM->PauseGame(false);
			dynamic_cast<Ranking*>(SM->GetScene("ranking"))->SetNewScore(dynamic_cast<Score*>(gameUI.find("score")->second)->GetScore());

			SM->SetScene("mainMenu");
			states = States::GAMEPLAY;
			dynamic_cast<UIPanel*>(gameUI.find("Pause")->second)->StopPress();

			death = false;

			dynamic_cast<Lives*>(gameUI.find("lives")->second)->SetLives(3);
			dynamic_cast<Score*>(gameUI.find("score")->second)->SetScore(0);

		}

		break;
	case Gameplay::DEATH:
		player->Update();

		if (!death)
		{

		    if (player->IsDead() == false)
			{
				TM->PauseGame(false);
				states = States::GAMEPLAY;

			}
		}
		else
		{
			dynamic_cast<Ranking*>(SM->GetScene("ranking"))->SetNewScore(dynamic_cast<Score*>(gameUI.find("score")->second)->GetScore());

			dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->ComproveButtonCol({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });

			if (dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->ComproveIfButtonPresed("returnGame"))
			{
				TM->PauseGame(false);
				player->returnGame();
				states = States::GAMEPLAY;
				RestartLevel();
				dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->StopPress();

			}

			if (dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->ComproveIfButtonPresed("returnMenu"))
			{
				TM->PauseGame(false);
				
				SM->SetScene("mainMenu");
				states = States::GAMEPLAY;

				dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->StopPress();

				death = false;

				dynamic_cast<Lives*>(gameUI.find("lives")->second)->SetLives(3);
				dynamic_cast<Score*>(gameUI.find("score")->second)->SetScore(0);
			}
		}
	

		break;
	case Gameplay::REACHEND:
		player->UpdateScore();





		if (reachEndTime + 2 < TM->GetCurrentTimeInPause())
		{
			if(endPosition != 0)
				states = States::GAMEPLAY;
			else
			{

				OnExit();

				level += 1;

				OnEnter();
				states = States::GAMEPLAY;

			}
			TM->PauseGame(false);
			player->end();

		}


		break;
	default:
		break;
	}











}

void Gameplay::Render()
{
	for (auto tile : tiles) {

		tile->Render();
	}
	for (auto object : objects) {
		if(object != nullptr)
		object->Render();
	}
	for (auto pos : endPositions)
	{
		pos->Render();
	}
	for (auto UI : gameUI)
	{
		if(UI.first != "gameOver" && UI.first != "Pause")
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
	case Gameplay::DEATH:
		player->Render();

		if (death)
		{
			dynamic_cast<UIPanel*>(gameUI.find("gameOver")->second)->Render();
		}
		break;
	case Gameplay::REACHEND:
		player->RenderScore();
		break;
	default:
		break;
	}





}

void Gameplay::OnEnter()
{
	AM->PlayMusic("GameplayMusic");

	text->SetText("Max Score " + std::to_string(dynamic_cast<Ranking*>(SM->GetScene("ranking"))->GetMaxScore()));

	if (level == 1)
	{
		LoadLevelFromFile("res/files/Level1.xml");
	}
	else if (level == 2)
	{
		LoadLevelFromFile("res/files/Level2.xml");

	}
	else
	{
		this->position = RM->gridY * 13;

		player->returnGame();
		TM->PauseGame(false);
		dynamic_cast<Ranking*>(SM->GetScene("ranking"))->SetNewScore(dynamic_cast<Score*>(gameUI.find("score")->second)->GetScore());

		SM->SetScene("mainMenu");
		states = States::GAMEPLAY;

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

	AM->StopAudios();
}

void Gameplay::SetObject(Object* object)
{
	if(object != nullptr)
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
