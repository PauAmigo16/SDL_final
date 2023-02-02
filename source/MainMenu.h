#pragma once
#include <unordered_map>
#include <map>
#include "Scene.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "UIButton.h"

class MainMenu :public Scene
{
private:
	std::map<std::string, UIButton*> myButton;
	bool audioIsOn;
public:
	MainMenu();
	bool gameExit;

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};