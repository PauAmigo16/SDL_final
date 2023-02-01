#pragma once
#include "GameObject.h"
#include "AnimatedImageRenderer.h"
#include "Log.h"

class Food :public GameObject
{
private:
	float leftLimit;
	float rightLimit;
	float moveVelocity;
	float isMoving;
	float movementTime;

	AnimatedImageRenderer* animation;

	bool movementDirection;

public:
	Food(float leftLimit, float logSize, Vector2 velocity, Vector2 startPosition);
	virtual ~Food() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual void SetPosition(Vector2 p);

	virtual bool IsFood() override;
};