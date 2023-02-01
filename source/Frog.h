#pragma once
#include"GameObject.h"
#include"AnimatedImageRenderer.h"
#include"Food.h"
#include"InputManager.h"
#include"AudioManager.h"

class Frog : public GameObject 
{
private:
	Vector2 startPosition;
	Vector2 move;

	bool dead;
	bool moving;
	bool hasFood;

	float movementTime;
	AnimatedImageRenderer animation;
	AnimatedImageRenderer deadAnimation;
	float deadAnimationTime;

	AnimatedImageRenderer foodAnimation;

	bool addFood;

public:
	Frog();

	Vector2 GetSpawnPos();
	void Respawn();

	bool IsMoving();

	void Update() override;
	void Render() override;

	void AddFood();

	virtual void SetPosition(Vector2 p) override;
	virtual void SetTransform(float x, float y, float w, float h, float rotation) override;

	bool IsDead();
	bool haveFood();

	void end();
	void returnGame();
};