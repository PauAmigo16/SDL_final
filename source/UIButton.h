#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "TextRenderer.h"
#include "AudioManager.h"

class UIButton:public GameObject
{
private:
	TextRenderer* text;
	SDL_Rect pos;
	SDL_Rect textPos;

public:
	bool InMousePos;
	bool Pressed;
	bool isClicked;

	UIButton(SDL_Rect target, std::string text);

	virtual void Update() override {}
	virtual void Render() override;

	void ComproveCollision(Vector2 point);

	void SetText(std::string mesage);
};

