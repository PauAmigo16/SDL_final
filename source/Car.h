#pragma once
#include "GameObject.h"
#include "TimeManager.h"

class Car:public GameObject
{
public:
	Car(Vector2 velocity, Vector2 startPosition, std::string id, int lenght, int rotation);
	virtual void Update() override;
	virtual void Render() override;
};

