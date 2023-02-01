#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	startTime = TM->GetCurrentTime();
	ImageRenderer* title[7];

	for (int i = 0; i < 7; i++)
	{

	AnimatedImageRenderer *animation = new AnimatedImageRenderer;

	animation->Load("resources/Assetsv1.png");
	animation->SetComponents(-90, { (int)(RM->windowWidht + ((RM->gridX*2) * i)), (int)(RM->windowHeight / 2), (int)RM->gridX, (int)RM->gridY }, 18, true);
	animation->SetImage({ 32,0,16,16 });
	animation->SetImage({ 16,0,16,16 });
	animation->SetImage({ 0,0,16,16 });
	animation->SetImage({ 32,0,16,16 });
	animation->SetVelocity({ (float)( - 9.333 * RM->gridX * TM->GetDeltaTime()),0});
	animaciones.push_back(animation);

	title[i] = new ImageRenderer;
	title[i]->Load("resources/Assetsv1.png");

	title[i]->SetPosition({ (float)(RM->windowWidht + ((RM->gridX * 2) * i) - ((RM->gridX / 2))), (float)((RM->windowHeight / 2)- (RM->gridY * 2)) });
	title[i]->SetScale((int)RM->gridX*2, (int)RM->gridY*2);

	title[i]->SetRotation(-90);
	title[i]->SetVelocity({ (float)(-9.333 * RM->gridX * TM->GetDeltaTime()),0 });
	this->title.push_back(title[i]);

	}

	title[0]->SetComponents({ 0,0,0 }, 255, 0, { 0,144,16,16 });
	title[1]->SetComponents({ 0,0,0 }, 255, 0, { 16,144,16,16 });
	title[2]->SetComponents({ 0,0,0 }, 255, 0, { 32,144,16,16 });
	title[3]->SetComponents({ 0,0,0 }, 255, 0, { 48,144,16,16 });
	title[4]->SetComponents({ 0,0,0 }, 255, 0, { 48,144,16,16 });
	title[5]->SetComponents({ 0,0,0 }, 255, 0, { 64,144,16,16 });
	title[6]->SetComponents({ 0,0,0 }, 255, 0, { 16,144,16,16 });


	//text = new TextRenderer({ 255,255,255 },255,0,{ (int)(RM->windowWidht / 4),(int)((RM->windowHeight / 2) + (RM->gridY * 2)),(int)(RM->windowWidht/2),(int)(RM->gridY) },"Press any button");
	//text->Load("resources/pixelart.ttf");
}

void SplashScreen::Update()
{
	if (startTime + 1.5f > TM->GetCurrentTime())
	{
		for (auto title : title)
		{
			title->Update();


		}
	}

	if (startTime + 3 > TM->GetCurrentTime())
	{
		for (auto anim : animaciones)
		{
			anim->Update();
		

		}
	}
	else
	{
		SM->SetScene("mainMenu");
	}




}

void SplashScreen::Render()
{
	for (auto anim : animaciones)
	{
		anim->Render();
	}
	for (auto title : title)
	{
		title->Render();


	}

	if (startTime + 3 < TM->GetCurrentTime())
	{
		//text->Render();

	}
}

void SplashScreen::OnEnter()
{

}

void SplashScreen::OnExit()
{
	for (auto anim : animaciones)
	{
		delete anim;
	}
	AM->StopAudios();
}
