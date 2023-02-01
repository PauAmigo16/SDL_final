#include "Crocodile.h"

Crocodile::Crocodile(Vector2 velocity, Vector2 startPosition, int pos)
{
	this->velocity.x = (velocity.x * TM->GetDT());
	this->velocity.y = (velocity.y * TM->GetDT());
	lethal = false;

	SetTransform(startPosition.x, startPosition.y, RM->gridX * 3, RM->gridY, 0);

	ImageRenderer* image = new ImageRenderer;
	image->Load("resources/Assetsv1.png");

	image->SetComponents({ 0,0,0 }, 255, 0, { 0,112,32,16 });




	if (pos)
	{	
		image->SetPosition({ (transform.GetPosition().x)+ RM->gridX, transform.GetPosition().y });

		image->flip = SDL_FLIP_HORIZONTAL;

	}
	else
	{
		image->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	}
	
	image->SetScale(RM->gridX * 2, transform.GetScale().y);
	image->SetVelocity(this->velocity);

	renderers.push_back(image);
}

void Crocodile::Update()
{
	SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });
	for (auto render : renderers)
	{
		render->Update();
	}
}

void Crocodile::Render()
{
	for (auto render : renderers)
	{
		render->Render();
	}
}
