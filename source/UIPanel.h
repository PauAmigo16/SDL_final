#pragma once
#include "GameObject.h"
#include "UIButton.h"
#include "InputManager.h"
#include "TextRenderer.h"

#include <unordered_map>

class UIPanel:public GameObject
{
private:
	TextRenderer* text;
	std::unordered_map <std::string, UIButton*> buttons;
public:
	UIPanel(SDL_Rect target, std::string mesage);
	virtual void Update() override;
	virtual void Render() override;
	void AddButton(SDL_Rect target, std::string name,std::string text);
	void ComproveButtonCol(Vector2 point);
	void StopPress();
	bool ComproveIfButtonPresed(std::string name);
};

