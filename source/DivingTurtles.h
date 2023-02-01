#pragma once
#include "Gameobject.h"
#include "AnimatedImageRenderer.h"

class DivingTurtles:public GameObject
{
private:
	float surfaceTime;
	float diveTime;
	float currentAnimationTime;
	float damageTime;
	std::vector<AnimatedImageRenderer*> divingAnimation;
	std::vector <AnimatedImageRenderer*> surfaceAnimation;
	bool isDiving;
public:
	DivingTurtles(int lenght, Vector2 velocity, Vector2 startPosition, int rotation);
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetPosition(Vector2 p);
	virtual ~DivingTurtles() override;

};

