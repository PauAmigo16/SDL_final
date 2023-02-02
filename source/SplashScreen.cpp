#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	time = TM->GetCurrentTime();
	ImageRenderer* title[7];
	ImageRenderer* entiLogo;
	int i = 0;
	while (i < 7)
	{

	title[i] = new ImageRenderer;
	entiLogo = new ImageRenderer;
	title[i]->Load("resources/Assetsv1.png");
	entiLogo->Load("resources/logo-enti.png");

	//entiLogo->SetPosition((int)(RM->windowWidht / 4), (int)((RM->windowHeight / 15) * 11), (int)(RM->windowWidht / 2), (int)((RM->windowHeight / 15) * 2));
	title[i]->SetPosition({ (float)(RM->windowWidht + ((RM->gridX * 2) * i) - ((RM->gridX / 2))), (float)((RM->windowHeight / 2)- (RM->gridY * 2)) });
	title[i]->SetScale((int)RM->gridX*2, (int)RM->gridY*2);

	//title[i]->SetRotation(-90);
	//title[i]->SetVelocity({ (float)(-9.333 * RM->gridX * TM->GetDT()),0 });
	this->frogger.push_back(title[i]);

	i++;
	}

	title[0]->SetComponents({ 0,0,0 }, 255, 0, { 0,144,16,16 });
	title[1]->SetComponents({ 0,0,0 }, 255, 0, { 16,144,10,16 });
	title[2]->SetComponents({ 0,0,0 }, 255, 0, { 32,144,16,16 });
	title[3]->SetComponents({ 0,0,0 }, 255, 0, { 48,144,16,16 });
	title[4]->SetComponents({ 0,0,0 }, 255, 0, { 48,144,16,16 });
	title[5]->SetComponents({ 0,0,0 }, 255, 0, { 64,144,16,16 });
	title[6]->SetComponents({ 0,0,0 }, 255, 0, { 16,144,16,16 });	
}

void SplashScreen::Update()
{
	if (time + 1.5f < TM->GetCurrentTime())
	{
		SM->SetScene("mainMenu");
	}
}

void SplashScreen::Render()
{
	auto enti=entiLogo;
	for (auto title : frogger)
	{
		title->Render();
		//enti->Render();
	}
}

void SplashScreen::OnEnter()
{

}

void SplashScreen::OnExit()
{
	AM->StopAudios();
}
