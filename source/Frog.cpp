#include "Frog.h"

Frog::Frog()
{
	this->velocity.x = 0;
	this->velocity.y = 0;
	moving = false;
	moveDelay = 0;
	dead = false;
	addFood = false;
	targetPosition = {(RM->windowWidht / 2) - (RM->gridX / 2), (RM->windowHeight / 15)*13};
	SetTransform(targetPosition.x, targetPosition.y, (RM->gridX), RM->gridY, 0);


	for (int i = 0; i < 2; i++)
	{
	ImageRenderer* image = new ImageRenderer;
	image->Load("resources/Assetsv1.png");
	image->SetComponents({ 0,0,0 }, 255, 0, { 32,i*16,16,16 });

	image->SetPosition({ transform.GetPosition().x, transform.GetPosition().y });
	image->SetScale(transform.GetScale().x, transform.GetScale().y);
	renderer.push_back(image);
	}




	animation.Load("resources/Assetsv1.png");
	animation.SetComponents(0,{ (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)transform.GetScale().x, (int)transform.GetScale().y }, 16,false);
	animation.SetImage({ 32,0,16,16 });
	animation.SetImage({16,0,16,16});
	animation.SetImage({ 0,0,16,16 });
	animation.SetImage({ 32,0,16,16 });

	foodAnimation.Load("resources/Assetsv1.png");
	foodAnimation.SetComponents(0, { (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)transform.GetScale().x, (int)transform.GetScale().y }, 16, false);
	foodAnimation.SetImage({ 32,16,16,16 });
	foodAnimation.SetImage({ 16,16,16,16 });
	foodAnimation.SetImage({ 0,16,16,16 });
	foodAnimation.SetImage({ 32,16,16,16 });


	deadAnimation.Load("resources/Assetsv1.png");
	deadAnimation.SetComponents(0, { (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)transform.GetScale().x, (int)transform.GetScale().y }, 10, false);
	deadAnimation.SetImage({ 0,64,16,16 });
	deadAnimation.SetImage({ 16,64,16,16 });
	deadAnimation.SetImage({ 32,64,16,16 });
	deadAnimation.SetImage({ 16,48,16,16 });
	deadAnimation.SetImage({ 32,48,16,16 });
	deadAnimation.SetImage({ 48,48,16,16 });
	deadAnimation.SetImage({ 0,48,16,16 });
	deadAnimation.SetImage({ 0,48,16,16 });
	deadAnimation.SetImage({ 0,48,16,16 });
	deadAnimation.SetImage({ 0,48,16,16 });

	deadAnimationTime = 2.0f;
}

Vector2 Frog::GetSpawnPos()
{
	return targetPosition;
}

void Frog::Respawn()
{
	dead = true;
	animation.SetRotation(0);
	deadAnimation.ActiveAnimation();
	moving = false;
	move = { 0,0 };
	moveDelay = TM->GetCurrentTimeInPause();
	addFood = false;

}
void Frog::AddMovement(Vector2 dir)
{
	
}

bool Frog::IsMoving()
{
	return moving;
}

void Frog::Update()
{
	if (!dead)
	{
		if (!moving)
		{
			//Si se mueve hacia los lados continua teniendo la velocidad del objeto en el que estaba, si se mueve en vertical pierde la velocidad del objeto en el que estaba para tener mas precision al jugar (aunque no deberia)
			if ((moveDelay + 0.1f) < TM->GetCurrentTime())
			{
				if (IM->CheckKeyState(SDLK_LEFT, PRESSED))
				{
					AM->PlaySFX("Jump", 0);

					movementTime = TM->GetCurrentTime();
					moving = true;
					move = { -4 * TM->GetDeltaTime() * RM->gridX,0 };
			
						foodAnimation.SetRotation(-90);
						foodAnimation.ActiveAnimation();
			
						animation.SetRotation(-90);
						animation.ActiveAnimation();
					
						renderer[0]->SetRotation(-90);
						renderer[1]->SetRotation(-90);
				}
				else if (IM->CheckKeyState(SDLK_RIGHT, PRESSED))
				{
					AM->PlaySFX("Jump", 0);

					movementTime = TM->GetCurrentTime();
					moving = true;
					move = { 4 * TM->GetDeltaTime() * RM->gridX,0 };
			
						foodAnimation.SetRotation(90);
						foodAnimation.ActiveAnimation();
			
						animation.SetRotation(90);
						animation.ActiveAnimation();
					
						renderer[0]->SetRotation(90);
						renderer[1]->SetRotation(90);
				}
				else if (IM->CheckKeyState(SDLK_UP, PRESSED))
				{
					AM->PlaySFX("Jump", 0);

					movementTime = TM->GetCurrentTime();
					moving = true;
					move = { 0,-4 * TM->GetDeltaTime() * RM->gridY };
				
						foodAnimation.SetRotation(0);
						foodAnimation.ActiveAnimation();
				
						animation.SetRotation(0);
						animation.ActiveAnimation();
					
						renderer[0]->SetRotation(0);
						renderer[1]->SetRotation(0);

						this->velocity.x = 0;
						this->velocity.y = 0;
				}
				else if (IM->CheckKeyState(SDLK_DOWN, PRESSED))
				{
					AM->PlaySFX("Jump", 0);

					movementTime = TM->GetCurrentTime();
					moving = true;
					move = { 0,4 * TM->GetDeltaTime() * RM->gridY };
				
						foodAnimation.SetRotation(180);
						foodAnimation.ActiveAnimation();
			
						animation.SetRotation(180);
						animation.ActiveAnimation();
					
						renderer[0]->SetRotation(180);
						renderer[1]->SetRotation(180);

						this->velocity.x = 0;
						this->velocity.y = 0;

				}
			}

		}
		else
		{
			if ((movementTime + 0.25f) < TM->GetCurrentTime())
			{

				moving = false;
				move = { 0,0 };
				moveDelay = TM->GetCurrentTime();
				SetPosition({ transform.GetPosition().x, round(transform.GetPosition().y / RM->gridY) * RM->gridY });

			}

		}

		if (transform.GetPosition().x + (velocity.x) < -(RM->gridX))
		{
			Respawn();
			moving = false;
			move = { 0,0 };


		}
		else if (transform.GetPosition().x + (velocity.x) > (RM->windowWidht)) {
			Respawn();

		}
		else
		{
			SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });

		}


		if (moving)
		{
			if (transform.GetPosition().x + (move.x) < 0 && move.x < 0)
			{
				SetPosition({ 0, transform.GetPosition().y + (move.y) });
				moving = false;
				move = { 0,0 };
			}
			else if (transform.GetPosition().x + (move.x) > (RM->windowWidht - RM->gridX) && move.x > 0) {
				SetPosition({ (RM->windowWidht - RM->gridX), transform.GetPosition().y + (move.y) });
				moving = false;
				move = { 0,0 };
			}
			else if (transform.GetPosition().y + (move.y) > (RM->windowHeight - (RM->gridX) * 2) && move.y > 0)
			{
				SetPosition({ transform.GetPosition().x + (move.x), (RM->windowHeight - (RM->gridX) * 2) });
				moving = false;
				move = { 0,0 };
			}
			else
			{
				SetPosition({ transform.GetPosition().x + (move.x), transform.GetPosition().y + (move.y) });

			}

		}

	}
	else
	{

		deadAnimation.Update();
	
		if ((moveDelay + deadAnimationTime) < TM->GetCurrentTimeInPause())
		{
			SetPosition(GetSpawnPos());
			dead = false;
			moveDelay = TM->GetCurrentTime();
		}
	}


	animation.Update();
	foodAnimation.Update();


	if (scoreObtained != nullptr)
	{
		if (scoreObtained->endAnimation == true)
		{
			delete scoreObtained;
			scoreObtained = nullptr;
		}
		else
		{
			scoreObtained->Update();
		}
    }

}

void Frog::Render()
{
	if (scoreObtained != nullptr)
	{
		scoreObtained->Render();

	}

	if (!dead)
	{
		if (moving) 
		{
			if (!addFood)
			{

				animation.Render();

			}
			else
			{
				foodAnimation.Render();

			}
		}
		else
		{
			if (!addFood)
			{

				renderer[0]->Render();

			}
			else
			{
				renderer[1]->Render();

			}
		}
		
	
		
	}
	else
	{
		deadAnimation.Render();
	}

}

void Frog::AddFood()
{
	addFood = true;
}

void Frog::SetPosition(Vector2 p)
{
	transform.SetPosition(p);
	boundingBox.SetTopLeft({ p.x + ((RM->windowWidht / 14) / 4),p.y + ((RM->windowHeight / 15) / 4) });
	foodAnimation.SetPosition(p);
	animation.SetPosition(p);

	deadAnimation.SetPosition(p);

	renderer[0]->SetPosition(p);
	renderer[1]->SetPosition(p);
}

void Frog::SetTransform(float x, float y, float w, float h, float rotation)
{
	transform.SetTransform(x, y, w, h, rotation);
	boundingBox.SetTopLeft({ x + ((RM->windowWidht / 14)/4),y + ((RM->windowHeight / 15) / 4) });
	boundingBox.SetSize({ (RM->windowWidht / 28),(RM->windowHeight / 30) });
}

bool Frog::IsDead()
{
	return dead;
}

bool Frog::haveFood()
{
	return addFood;
}

void Frog::end()
{
	animation.SetRotation(0);
	moving = false;
	move = { 0,0 };
	moveDelay = TM->GetCurrentTime();
	addFood = false;
	SetPosition(GetSpawnPos());
	moveDelay = TM->GetCurrentTime();

}

void Frog::addScoreObtainedImage(bool MaxScore, Vector2 startPosition)
{

	scoreObtained = new ScoreObtained(MaxScore, startPosition);

}

void Frog::returnGame()
{
	SetPosition(GetSpawnPos());
	dead = false;
	moveDelay = TM->GetCurrentTime();

}

void Frog::RenderScore()
{
	if(scoreObtained != nullptr)
	scoreObtained->Render();
}

void Frog::UpdateScore()
{
	if (scoreObtained != nullptr)
	scoreObtained->Update();
}
