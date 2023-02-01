#pragma once
#include "Gameobject.h"
#include "AnimatedImageRenderer.h"

class CrocodileMouth : public GameObject
{
private: 
	bool mouthOpen;
	float timeController;
	float timeWithMouthOpen;
	float timeWithMouthClose;
public:
	CrocodileMouth(Vector2 velocity, Vector2 startPosition, int pos);
	virtual void Update() override;
	virtual void Render() override;
};

