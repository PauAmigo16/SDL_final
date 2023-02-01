#pragma once
#include <map>
#include <string>
#include <assert.h>

#include "Scene.h"

#define SM SceneManager::GetInstance()


class SceneManager {
private:
	static SceneManager* instance;
	std::map<std::string, Scene*> scenes;
	Scene* currentScene;

	SceneManager();


public:
	static SceneManager* GetInstance();

	void AddScene(std::string name, Scene* s);

	//template <class S> S* GetScene();
	Scene* GetScene(std::string name);

	Scene* GetCurrentScene();

	//Hacen lo mismo
	template <class S> void SetScene();
	void SetScene(std::string name);


};

template<class S>
inline void SceneManager::SetScene()
{
}
