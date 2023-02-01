#include "CrocodileMouth.h"

CrocodileMouth::CrocodileMouth(Vector2 velocity, Vector2 startPosition, int pos)
{
	this->velocity.x = (velocity.x * TM->GetDT());
	this->velocity.y = (velocity.y * TM->GetDT());
	lethal = false;

	SetTransform(startPosition.x, startPosition.y, RM->gridX, RM->gridY, 0);

	for (int i = 0; i < 2; i++)
	{
		ImageRenderer* image = new ImageRenderer;
		image->Load("resources/Assetsv1.png");

		image->SetComponents({ 0,0,0 }, 255, 0, { 32+(i*16),112,16,16});


		if (pos)
		{
			image->flip = SDL_FLIP_HORIZONTAL;
		}

			image->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });

		image->SetScale(transform.GetScale().x, transform.GetScale().y);

		image->SetVelocity(this->velocity);
		renderers.push_back(image);
	}
	timeController = TM->GetCurrentTime();
	timeWithMouthOpen = 1 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	timeWithMouthClose = 1 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void CrocodileMouth::Update()
{
	if ((timeController + timeWithMouthOpen) < TM->GetCurrentTime() && mouthOpen == true)
	{
		mouthOpen = false;
		timeController = TM->GetCurrentTime();
		lethal = false;

	}
	else if ((timeController + timeWithMouthClose) < TM->GetCurrentTime() && mouthOpen == false)
	{
		mouthOpen = true;
		timeController = TM->GetCurrentTime();
		lethal = true;
	}



	SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });
	for (auto render : renderers)
	{
		render->Update();
	}
}

void CrocodileMouth::Render()
{
	if(!mouthOpen)
		renderers[1]->Render();
	else
		renderers[0]->Render();

}
