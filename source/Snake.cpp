#include "Snake.h"


Snake::Snake(float leftLimit, float logSize, float moveVelocity, Vector2 velocity, Vector2 startPosition)
{
	this->velocity.x = (velocity.x * TM->GetDeltaTime());
	this->velocity.y = (velocity.y * TM->GetDeltaTime());

	this->leftLimit = leftLimit;
	this->rightLimit = logSize;

	this->moveVelocity = (moveVelocity * TM->GetDeltaTime()* RM->gridX);


	getDamage = true;

	SetTransform(startPosition.x, startPosition.y, (RM->gridX *1.5f), RM->gridY * 0.75f, 0);
	
	animation = new AnimatedImageRenderer;
	animation->flip = SDL_FLIP_HORIZONTAL;

	animation->Load("resources/Assetsv1.png");

	animation->SetComponents(0, { (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)((RM->gridX * 1.5f)), (int)(RM->gridY * 0.75f) }, 6, true);
	animation->SetImage({ 0,128,32,16 });
	animation->SetImage({ 32,128,32,16 });
	animation->SetImage({ 64,128,32,16 });

}

void Snake::Update()
{


	if (((transform.GetPosition().x + (velocity.x) + moveVelocity) < leftLimit)&& moveVelocity < 0)
	{
		moveVelocity = -moveVelocity;
		animation->flip = SDL_FLIP_HORIZONTAL;
	}
	else if ((transform.GetPosition().x + (velocity.x) + moveVelocity > (leftLimit+ rightLimit)) && moveVelocity > 0)
	{
		moveVelocity = -moveVelocity;
		animation->flip = SDL_FLIP_NONE;
	}

	leftLimit += (velocity.x);
	SetPosition({ transform.GetPosition().x + (velocity.x) + moveVelocity, transform.GetPosition().y + (velocity.y) });

	animation->Update();

}

void Snake::Render()
{
	animation->Render();
}

Snake::~Snake()
{
	delete animation;
}

void Snake::SetPosition(Vector2 p)
{
	transform.SetPosition(p);
	boundingBox.SetTopLeft(p);
	animation->SetPosition(p);
}
