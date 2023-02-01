#include "Turtles.h"

Turtles::Turtles(int lenght, Vector2 velocity, Vector2 startPosition, int rotation)
{
	this->velocity.x = (velocity.x * TM->GetDT());
	this->velocity.y = (velocity.y * TM->GetDT());
	getDamage = false;

	SetTransform(startPosition.x, startPosition.y, RM->gridX * lenght, RM->gridY, rotation);
	for (int i = 0; i < lenght; i++)
	{
		ImageRenderer* image = new ImageRenderer;
		image->Load("resources/Assetsv1.png");
		image->SetComponents({ 0,0,0 }, 255, 0, { 0,80,16,16 });
		image->SetRotation(transform.GetRotation());
		image->SetPosition({ (transform.GetPosition().x + (RM->gridX * i)), transform.GetPosition().y });
		image->SetScale(transform.GetScale().x / lenght, transform.GetScale().y);
		image->SetVelocity(this->velocity);
		renderer.push_back(image);
	}
}

void Turtles::Update()
{
	SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });
	for (auto render : renderer)
	{
		render->Update();
	}
}

void Turtles::Render()
{
	for (auto render : renderer)
	{
		render->Render();
	}
}
