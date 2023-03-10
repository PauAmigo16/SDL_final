#include "Food.h"

Food::Food(float logPos, float logSize, Vector2 velocity, Vector2 startPosition)
{
	this->velocity.x = (velocity.x * TM->GetDT());
	this->velocity.y = (velocity.y * TM->GetDT());

	this->leftLimit = logPos;
	this->rightLimit = logSize;

	this->moveVelocity = (moveVelocity * TM->GetDT() * RM->gridX);

	lethal = false;
	isMoving = false;

	movementTime = TM->GetCurrentTime()-1;
	moveVelocity = 0;
	movementDirection = false;

	SetTransform(startPosition.x, startPosition.y, (RM->gridX), RM->gridY, 0);

	animation = new AnimatedImageRenderer;

	animation->Load("resources/Assetsv1.png");

	animation->SetComponents(90, { (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)((RM->gridX)), (int)(RM->gridY) }, 4, false);
	animation->SetImage({ 32,32,16,16 });
	animation->SetImage({ 16,32,16,16 });
	animation->SetImage({ 0,32,16,16 });
	animation->SetImage({ 32,32,16,16 });

}

Food::~Food()
{
	delete animation;
}

void Food::Update()
{
	leftLimit += (velocity.x);

	if ((movementTime + 1 < TM->GetCurrentTime()) && !isMoving)
	{
		movementTime = TM->GetCurrentTime();
		isMoving = true;

		if (movementDirection)
		{
			moveVelocity = -(RM->gridX * TM->GetDT());

			if (transform.GetPosition().x - (RM->gridX / 2) < leftLimit)
			{
				movementDirection = false;
				moveVelocity = (RM->gridX * TM->GetDT());
				animation->SetRotation(90);
			}

		}
		else
		{
			moveVelocity = (RM->gridX * TM->GetDT());

			if (transform.GetPosition().x + (RM->gridX/2) > (leftLimit + rightLimit))
			{
				movementDirection = true;
				moveVelocity = -(RM->gridX * TM->GetDT());
				animation->SetRotation(-90);

			}
		}
		animation->ActiveAnimation();
	}
	else if ((movementTime + 1 < TM->GetCurrentTime()) && isMoving)
	{
		movementTime = TM->GetCurrentTime();
		isMoving = false;
		moveVelocity = 0;

	}

	animation->Update();

	SetPosition({ transform.GetPosition().x + (velocity.x) + moveVelocity, transform.GetPosition().y + (velocity.y) });
}

void Food::Render()
{
	animation->Render();
}

void Food::SetPosition(Vector2 p)
{
	transform.SetPosition(p);
	boundingBox.SetTopLeft(p);
	animation->SetPosition(p);
}

bool Food::IsFood()
{
	return true;
}


