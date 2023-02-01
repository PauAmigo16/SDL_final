#pragma once
#include "GameObject.h"

class Turtles: public GameObject
{
public:
	Turtles(int lenght, Vector2 velocity, Vector2 startPosition, int rotation);
	virtual void Update() override;
	virtual void Render() override;
};

