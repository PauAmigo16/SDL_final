#pragma once
#include "GameObject.h"
#include "TextRenderer.h"

class Lives:public GameObject
{
private:
	int lives;
	
	TextRenderer* text;
	SDL_Rect pos;
	SDL_Rect textPos;

public:
	Lives();

	virtual void Update() override {}
	virtual void Render() override;

	int GetLives();

	void LostLive();

	void SetLives(int value);
};

