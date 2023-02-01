#include "Lives.h"

Lives::Lives()
{

	SetTransform((RM->gridX / 2), (RM->gridY * 14) + (RM->gridY / 4), RM->gridX / 2, RM->gridY / 2, 0);

	for (int i = 0; i < 3; i++)
	{
		ImageRenderer* image = new ImageRenderer;
		image->Load("resources/Assetsv1.png");

		image->SetComponents({ 0,0,0 }, 255, 0, { 64,96,16,16 });

		image->SetPosition({ (transform.GetPosition().x) + (RM->gridX*i) , transform.GetPosition().y});
		image->SetScale(transform.GetScale().x, transform.GetScale().y);
		renderer.push_back(image);
	}
	lives = 3;
}

void Lives::Update()
{

}

void Lives::Render()
{
	for(int i = 0; i < lives; i++)
	{
		renderer[i]->Render();
	}
}

int Lives::GetLives()
{
	return lives;
}

void Lives::LostLive()
{
	lives--;
}

void Lives::SetLives(int value)
{
	lives = value;
}
