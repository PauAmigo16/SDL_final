#pragma once
#include "GameObject.h"
#include "AnimatedImageRenderer.h"

class EndPosition: public GameObject
{
private:
	AnimatedImageRenderer crocodile;
	ImageRenderer fly;
	ImageRenderer frogImage;
	float timeControl;
public:		
	bool addCrocodile;
	bool addFly;
	bool frog;
	EndPosition(Vector2 position);
	virtual void Update() override;
	virtual void Render() override;
	void ActiveAnimatios();
};

