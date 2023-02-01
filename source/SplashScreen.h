#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "AnimatedImageRenderer.h"
#include "TextRenderer.h"

#include <iostream>
class SplashScreen :public Scene
{
private: 
	float startTime;
	std::vector<AnimatedImageRenderer*> animaciones;
	std::vector<ImageRenderer*> title;
	TextRenderer* text;
public:
	SplashScreen();
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};