#include "Car.h"

Car::Car(Vector2 velocity, Vector2 startPosition, std::string id, int lenght, int rotation)
{
	this->velocity.x = (velocity.x*TM->GetDeltaTime());
	this->velocity.y = (velocity.y * TM->GetDeltaTime());
	getDamage = true;

	SetTransform(startPosition.x, startPosition.y, RM->gridX * lenght, RM->gridY, rotation);

	ImageRenderer* image = new ImageRenderer;
	image->Load("resources/Assetsv1.png");
	if (id == "racing0")
		image->SetComponents({ 0,0,0 }, 255, 0, { 48,0,16,16 });

	else if (id == "farming0")
		image->SetComponents({ 0,0,0 }, 255, 0, { 64,0,16,16 });

	else if (id == "family0")
		image->SetComponents({ 0,0,0 }, 255, 0, { 112,0,16,16 });

	else if (id == "racing1")
		image->SetComponents({ 0,0,0 }, 255, 0, { 128,0,16,16 });

	else if (id == "truck0")
		image->SetComponents({ 0,0,0 }, 255, 0, { 80,0,32,16 });
	else
		assert(0);



	image->SetRotation(transform.GetRotation());

	image->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	image->SetScale(transform.GetScale().x, transform.GetScale().y);
	image->SetVelocity(this->velocity);
	renderer.push_back(image);
}

void Car::Update()
{
	SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });
	for (auto render : renderer)
	{
		render->Update();
	}
}

void Car::Render()
{
	for (auto render : renderer)
	{
		render->Render();
	}
}
