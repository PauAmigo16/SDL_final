#include "ScoreObtained.h"

ScoreObtained::ScoreObtained(bool MaxScore, Vector2 startPosition)
{
	endAnimation = false;

	startTime = TM->GetCurrentTime();

	SetTransform(startPosition.x + (RM->gridX/8), startPosition.y, RM->gridX, RM->gridY, 0);

	animation.Load("resources/Assetsv1.png");
	animation.SetComponents(0, { (int)(transform.GetPosition().x), (int)transform.GetPosition().y, (int)transform.GetScale().x, (int)transform.GetScale().y }, 16, false);
	animation.SetImage({ 16,48,16,16 });
	animation.SetImage({ 32,48,16,16 });
	animation.SetImage({ 48,48,16,16 });
	if (MaxScore)
		animation.SetImage({ 16,96,16,16 });
	else
		animation.SetImage({ 0,96,16,16 });

}

void ScoreObtained::Update()
{
	if (startTime + 0.5f < TM->GetCurrentTime())
	{
		endAnimation = true;

	}
	else
	{
		animation.Update();
	}
}

void ScoreObtained::Render()
{
	animation.Render();
}
