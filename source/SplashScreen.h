#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "AnimatedImageRenderer.h"
#include "TextRenderer.h"

#include <iostream>
class SplashScreen :public Scene
{
private: 
	ImageRenderer* entiLogo;
	std::vector<ImageRenderer*> frogger;
	float time=0.0f;
public:
	SplashScreen();
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};