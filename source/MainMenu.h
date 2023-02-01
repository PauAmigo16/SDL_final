#pragma once
#include "Scene.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "AudioManager.h"

#include <unordered_map>
class MainMenu :public Scene
{
private:
	std::unordered_map<std::string, UIButton*> buttons;
	bool audioOn;
public:
	bool exitGame;
	MainMenu();

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};