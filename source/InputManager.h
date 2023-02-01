#pragma once
#include <unordered_map>
#include <SDL.h>
#include "RenderManager.h"

enum KeyState { UNDEFINED = 1, DOWN = 2, PRESSED = 4, UP = 8, RELEASED = 16 };

#define IM InputManager::GetInstance()
class InputManager {
private:
	std::unordered_map<Sint32, KeyState> keys;
	int mouseX, mouseY;
	bool quitEvent;
	InputManager() : quitEvent(false), mouseX(0), mouseY(0) {}
	static InputManager* instance;
public:
	bool mousePressed;
	static InputManager* GetInstance();
	void Listen();
	bool CheckKeyState(Sint32 key, KeyState state);
	int GetMouseX();
	int GetMouseY();
	bool GetQuitEvent();
};
