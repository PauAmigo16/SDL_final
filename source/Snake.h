#pragma once
#include "GameObject.h"
#include "AnimatedImageRenderer.h"
#include "Log.h"

class Snake:public GameObject
{
private:
	float leftLimit;
	float rightLimit;
	float moveVelocity;
	AnimatedImageRenderer* animation;
public:
	Snake(float leftLimit, float logSize, float moveVelocity,Vector2 velocity, Vector2 startPosition);
	virtual void Update() override;
	virtual void Render() override;
	virtual ~Snake() override;
	virtual void SetPosition(Vector2 p);

};

