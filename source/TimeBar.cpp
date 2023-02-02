#include "TimeBar.h"

TimeBar::TimeBar()
{



	 SetTransform(RM->windowWidht /4, (RM->gridY*14)+ (RM->gridY/4), RM->windowWidht/2, RM->gridY/2, 0);

	 ImageRenderer* image = new ImageRenderer;
	 image->Load("resources/Assetsv2.png");
	 image->SetComponents({ 0,0,0 }, 255, 0, { 122,195,5,5});

	 image->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	 image->SetScale(transform.GetScale().x, transform.GetScale().y);
	
	 renderers.push_back(image);
}

void TimeBar::Update()
{
	if (TM->GetCurrentTime() > startTime)
		barSize = 1 - ((TM->GetCurrentTime() - startTime) / maxTime);
	else
		barSize = 1;

	renderers[0]->SetScale(transform.GetScale().x* barSize, transform.GetScale().y);
}

void TimeBar::Render()
{
	renderers[0]->Render();
}



void TimeBar::SetStartTime(float time)
{
	startTime = time;
}

void TimeBar::SetMaxTime(float time)
{
	maxTime = time;

}

int TimeBar::GetPerc()
{
	return (1 -((TM->GetCurrentTime() - startTime) / maxTime))*100;
}
