#include "EndPosition.h"

EndPosition::EndPosition(Vector2 position)
{
	getDamage = false;
	frog = false;
	SetTransform(position.x, position.y, (RM->gridX), RM->gridY, 0);

	crocodile.flip = SDL_FLIP_NONE;
	crocodile.SetRotation(90);

	crocodile.Load("resources/Assetsv1.png");
	fly.Load("resources/Assetsv1.png");
	frogImage.Load("resources/Assetsv1.png");

	frogImage.SetComponents({ 0,0,0 }, 255, 0, { 48,96,16,16 });
	frogImage.SetPosition({ position.x +(RM->windowWidht / 66),position.y + (RM->gridY / 5)});
	frogImage.SetScale((RM->windowWidht / 16.5f), RM->gridY/1.5f);

	fly.SetComponents({ 0,0,0 }, 255, 0, { 32,96,16,16 });
	fly.SetPosition({ position.x,position.y });
	fly.SetScale(RM->windowWidht/11, RM->gridY);

	crocodile.SetComponents(0, { (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)RM->windowWidht / 11, (int)(RM->gridY) }, 10, false);
	crocodile.SetImage({ 80,96,16,16 });
	crocodile.SetImage({ 80,96,16,16 });
	crocodile.SetImage({ 96,96,16,16 });
	crocodile.SetImage({ 96,96,16,16 });
	crocodile.SetImage({ 96,96,16,16 });
	crocodile.SetImage({ 96,96,16,16 });
	crocodile.SetImage({ 96,96,16,16 });
	crocodile.SetImage({ 96,96,16,16 });
	crocodile.SetImage({ 80,96,16,16 });
	crocodile.SetImage({ 80,96,16,16 });

}

void EndPosition::Update()
{
	if (addCrocodile)
	{
		crocodile.Update();

		if (timeControl + 1 < TM->GetCurrentTime())
		{
			addCrocodile = false;
		}
		getDamage = true;

	}
	else if (addFly)
	{
		if (timeControl + 5 < TM->GetCurrentTime())
		{
			addFly = false;
		}
		getDamage = false;

	}
	else if(frog)
	{
		getDamage = true;
	}
	else
	{
		getDamage = false;

	}

}

void EndPosition::Render()
{
	if (addCrocodile)
	{
		crocodile.Render();

	}
	else if (addFly)
	{
		fly.Render();
	}
	else if (frog)
	{

		frogImage.Render();
	}
}

void EndPosition::ActiveAnimatios()
{
	crocodile.ActiveAnimation();
	timeControl = TM->GetCurrentTime();
}
