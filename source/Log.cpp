#include "Log.h"

Log::Log(int lenght, Vector2 velocity, Vector2 startPosition)
{
	this->velocity.x = (velocity.x * TM->GetDT());
	this->velocity.y = (velocity.y * TM->GetDT());
	lethal = false;

	SetTransform(startPosition.x, startPosition.y, RM->gridX *lenght, RM->gridY, 0);

	for (int i = 0; i < lenght; i++)
	{
	ImageRenderer* image = new ImageRenderer;
	image->Load("resources/Assetsv1.png");

	if(i == 0)
		image->SetComponents({ 0,0,0 }, 255, 0, {96,128,16,16});
	else if(i == lenght-1)
		image->SetComponents({ 0,0,0 }, 255, 0, { 128,128,16,16 });
	else 
		image->SetComponents({ 0,0,0 }, 255, 0, { 112,128,16,16 });


	image->SetPosition({ (transform.GetPosition().x + (RM->gridX * i)), transform.GetPosition().y });
	image->SetScale( transform.GetScale().x/lenght , transform.GetScale().y);
	image->SetVelocity(this->velocity);

	renderers.push_back(image);
	}

	food = false;
	object = nullptr;
}

Log::~Log()
{

	if (object != nullptr)
	{
		delete object;

	}
}

void Log::Update()
{
	if (object != nullptr)
	{
		object->Update();
	}

	SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });

	for (auto render : renderers)
	{
		render->Update();
	}
}

void Log::Render()
{
	for (auto render : renderers)
	{
		render->Render();
	}
	if (object != nullptr)
	{
		object->Render();
	}
}

void Log::SetObject(Object* object)
{
	this->object = object;
}

void Log::SetFood()
{
	food = true;
}

bool Log::IsFood()
{
	return food;
}

Object* Log::GetObject()
{
	return object;
}

void Log::deleteFood()
{
	delete object;
	object = nullptr;
	food = false;
}


