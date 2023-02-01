#include "InputManager.h"


InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance() {
	if (instance == nullptr)
		instance = new InputManager();
	return instance;
}

//Processes all the SDL input events and updates the keys map
void InputManager::Listen() {
	//Hacer Update de los eventos actuales
	for (auto i = keys.begin(); i != keys.end(); i++) {
		if ((i->second & DOWN) > 0)
			i->second = PRESSED;
		else if ((i->second & UP) > 0)
			i->second = RELEASED;
	}

	//Mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	//Procesar los eventos de SDL
	SDL_Event evt;

	
	while (SDL_PollEvent(&evt)) {
		if (evt.type == SDL_QUIT) {
			quitEvent = true;
		}
		else if (evt.type == SDL_KEYDOWN) {
			keys[evt.key.keysym.sym] = (KeyState)(DOWN | PRESSED);
		}
		else if (evt.type == SDL_KEYUP) {
			keys[evt.key.keysym.sym] = (KeyState)(UP | RELEASED);
		}
		else if (evt.type == SDL_MOUSEBUTTONDOWN)
		{
			mousePressed = true;
		}
		else if (evt.type == SDL_MOUSEBUTTONUP)
		{
			mousePressed = false;

		}
		else if (evt.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			SDL_RenderSetScale(RM->GetRenderer(), evt.window.data1/RM->windowWidht, evt.window.data2 / RM->windowHeight);
			SDL_RenderPresent(RM->GetRenderer());
		}
	}
}

//Returns true if the key is in the give state
bool InputManager::CheckKeyState(Sint32 key, KeyState state) {
	if (keys.find(key) != keys.end()) {
		//Check if state == Value
		return ((int)keys[key] & (int)state) > 0;
	}
	else {
		keys.emplace(key, UNDEFINED);
		return (state & UNDEFINED) > 0;
	}
}

int InputManager::GetMouseX() {
	return mouseX;
}
int InputManager::GetMouseY() {
	return mouseY;
}
bool InputManager::GetQuitEvent() {
	return quitEvent;
}