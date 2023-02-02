#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	time = TM->GetCurrentTime();
	FrogRender();
	EntiRender();
}

void SplashScreen::Update()
{
	if (time + 3.0f < TM->GetCurrentTime())
	{
		SM->SetScene("mainMenu");
	}
}
void SplashScreen::EntiRender()
{
	entiLogo = new ImageRenderer();
	entiLogo->Load("resources/logo-enti.png");
	entiLogo->SetPosition({ (float)((RM->windowWidht / 2) - (RM->gridY * 4 / 2)), (float)(RM->windowHeight / 2) + (RM->gridY * 2 / 2) });
	entiLogo->SetScale((int)RM->gridX * 4, (int)RM->gridY * 4);
	entiLogo->SetComponents({ 0,0,0 }, 255, 0, { 0,0,255,255 });
}
void SplashScreen::FrogRender()
{
	ImageRenderer* froggerTitle[7];
	int i = 0;
	while (i < 7)
	{
		froggerTitle[i] = new ImageRenderer;

		froggerTitle[i]->Load("resources/Assetsv1.png");

		froggerTitle[i]->SetPosition({ (float)(16 * 6 * i), (float)((RM->windowHeight / 2) - (RM->gridY * 2)) });
		froggerTitle[i]->SetScale((int)RM->gridX * 2, (int)RM->gridY * 2);

		this->frogger.push_back(froggerTitle[i]);

		i++;
	}
	froggerTitle[0]->SetComponents({ 0,0,0 }, 255, 0, { 0,144,16,16 });
	froggerTitle[1]->SetComponents({ 0,0,0 }, 255, 0, { 16,144,16,16 });
	froggerTitle[2]->SetComponents({ 0,0,0 }, 255, 0, { 32,144,16,16 });
	froggerTitle[3]->SetComponents({ 0,0,0 }, 255, 0, { 48,144,16,16 });
	froggerTitle[4]->SetComponents({ 0,0,0 }, 255, 0, { 48,144,16,16 });
	froggerTitle[5]->SetComponents({ 0,0,0 }, 255, 0, { 64,144,16,16 });
	froggerTitle[6]->SetComponents({ 0,0,0 }, 255, 0, { 16,144,16,16 });
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
	AM->MuteAudio();
}
