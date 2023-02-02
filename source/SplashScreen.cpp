#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	time = TM->GetCurrentTime();
	ImageRenderer* title[7];
	int i = 0;
	while (i < 7)
	{
	title[i] = new ImageRenderer;
	
	title[i]->Load("resources/Assetsv1.png");

	title[i]->SetPosition({ (float)(16*6*i), (float)((RM->windowHeight / 2)- (RM->gridY * 2)) });
	title[i]->SetScale((int)RM->gridX*2, (int)RM->gridY*2);

	this->frogger.push_back(title[i]);

	i++;
	}

	entiLogo = new ImageRenderer();
	entiLogo->Load("resources/logo-enti.png");
	entiLogo->SetPosition({ (float)(RM->windowWidht / 4), (float)(16*4) });
	entiLogo->SetComponents({ 0,0,0 }, 255, 0, { 0,144,200,200 });


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
	for (auto title : frogger)
	{
		title->Render();
	}
	entiLogo->Render();
}

void SplashScreen::OnExit()
{
	AM->StopAudios();
}
