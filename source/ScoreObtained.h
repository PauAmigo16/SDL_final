#pragma once
#include "GameObject.h"
#include "AnimatedImageRenderer.h"

class ScoreObtained:public GameObject
{
private:
	float startTime;
	AnimatedImageRenderer animation;
public:
	bool endAnimation;
	ScoreObtained(bool MaxScore, Vector2 startPosition);
	virtual void Update() override;
	virtual void Render() override;

};

