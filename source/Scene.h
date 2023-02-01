#pragma once
#include <vector>
#include"AudioManager.h"
#include"InputManager.h"
#include"TimeManager.h"
#include"RenderManager.h"
#include"Object.h"



class Scene {
protected:
	std::vector<Object*> UI;
	std::vector<Object*> objects;
public:
		Scene();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
};