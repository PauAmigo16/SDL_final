#include "DivingTurtles.h"

DivingTurtles::DivingTurtles(int lenght, Vector2 velocity, Vector2 startPosition, int rotation)
{
	this->velocity.x = (velocity.x * TM->GetDeltaTime());
	this->velocity.y = (velocity.y * TM->GetDeltaTime());
	getDamage = false;
	isDiving = false;

	SetTransform(startPosition.x, startPosition.y, RM->gridX * lenght, RM->gridY, rotation);

	for (int i = 0; i < lenght; i++)
	{
		AnimatedImageRenderer* divingAnimation = new AnimatedImageRenderer;
		AnimatedImageRenderer* surfaceAnimation = new AnimatedImageRenderer;

		divingAnimation->Load("resources/Assetsv1.png");
		surfaceAnimation->Load("resources/Assetsv1.png");

		divingAnimation->SetComponents(rotation, { (int)(transform.GetPosition().x)+ (int)(i* RM->gridX), (int)transform.GetPosition().y, (int)RM->gridX, (int)RM->gridY}, 5, false);
		divingAnimation->SetImage({ 0,80,16,16 });
		divingAnimation->SetImage({ 16,80,16,16 });
		divingAnimation->SetImage({ 32,80,16,16 });
		divingAnimation->SetImage({ 48,80,16,16 });
		divingAnimation->SetImage({ 64,80,16,16 });

		surfaceAnimation->SetComponents(rotation, { (int)(transform.GetPosition().x) + (int)(i * RM->gridX), (int)transform.GetPosition().y, (int)RM->gridX, (int)RM->gridY }, 5, false);
		surfaceAnimation->SetImage({ 64,80,16,16 });
		surfaceAnimation->SetImage({ 48,80,16,16 });
		surfaceAnimation->SetImage({ 32,80,16,16 });
		surfaceAnimation->SetImage({ 16,80,16,16 });
		surfaceAnimation->SetImage({ 0,80,16,16 });

		this->divingAnimation.push_back(divingAnimation);
		this->surfaceAnimation.push_back(surfaceAnimation);

	}	
	currentAnimationTime = TM->GetCurrentTime();
	surfaceTime = (3 + (rand() % 4)) + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	diveTime = 1 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void DivingTurtles::Update()
{
	SetPosition({ transform.GetPosition().x + (velocity.x), transform.GetPosition().y + (velocity.y) });


	if ((currentAnimationTime + surfaceTime) < TM->GetCurrentTime() && isDiving == false)
	{
		currentAnimationTime = TM->GetCurrentTime();
		isDiving = true;
		for (auto anim : divingAnimation)
		{
			anim->ActiveAnimation();

		}
		damageTime = TM->GetCurrentTime();

	}
	else if ((currentAnimationTime + diveTime) < TM->GetCurrentTime() && isDiving == true)
	{
		currentAnimationTime = TM->GetCurrentTime();
		isDiving = false;
		for (auto anim : surfaceAnimation)
		{
			anim->ActiveAnimation();

		}
		damageTime = TM->GetCurrentTime();
	}


	if (isDiving)
	{
		for (auto anim : divingAnimation)
		{
			anim->Update();

		}
		//No hace daño hasta que no pasa 1 segundo de la animacion(la animacion completa)
		if (damageTime + 1.0f < TM->GetCurrentTime())
		{
			getDamage = true;
		}
	}
	else
	{
		for (auto anim : surfaceAnimation)
		{
			anim->Update();

		}
		//Deja de hacer daño despues de 0.5s (la mitad de la animacion)
		if (damageTime + 0.5f < TM->GetCurrentTime())
		{
			getDamage = false;
		}
	}
}

void DivingTurtles::Render()
{
	if(isDiving)
	{ 
		for (auto anim : divingAnimation)
		{
			anim->Render();

		}
	}
	else
	{
		for (auto anim : surfaceAnimation)
		{
			anim->Render();

		}
	}
}

void DivingTurtles::SetPosition(Vector2 p)
{
	transform.SetPosition(p);
	boundingBox.SetTopLeft(p);
	for (int i = 0; i < divingAnimation.size(); i++)
	{
	divingAnimation[i]->SetPosition({p.x+(i*RM->gridX),p.y});

	}
	for (int i = 0; i < surfaceAnimation.size(); i++)
	{
		surfaceAnimation[i]->SetPosition({ p.x + (i * RM->gridX),p.y });

	}

}

DivingTurtles::~DivingTurtles()
{
	for (auto images : divingAnimation)
	{
		delete images;
	}
	for (auto images : surfaceAnimation)
	{
		delete images;
	}
	for (auto images : renderer)
	{
		delete images;
	}
}
