#pragma once
#include "GameObject.h"

class Lives:public GameObject
{
private:
	int lives;
public:
	Lives();
	virtual void Update() override;	
	virtual void Render() override;
	int GetLives();
	void LostLive();
	void SetLives(int value);
};

