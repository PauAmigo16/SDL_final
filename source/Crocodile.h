#pragma once
#include "Gameobject.h"

class Crocodile: public GameObject
{
public:
	Crocodile(Vector2 velocity, Vector2 startPosition, int pos);
	virtual void Update() override;
	virtual void Render() override;
};

