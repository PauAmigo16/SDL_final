#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::AddScene(std::string name, Scene* s)
{
	scenes.emplace(name, s);
}

Scene* SceneManager::GetScene(std::string name)
{
	auto scene = scenes.find(name);
	bool sceneFound = scene != scenes.end();

	return sceneFound ? scenes[name] : nullptr;
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::SetScene(std::string name)
{
	auto scene = scenes.find(name);

	bool sceneFound = scene != scenes.end();

	//Stop code
	assert(sceneFound);
	if (sceneFound)
	{
		if (currentScene != nullptr)
			currentScene->OnExit();
		currentScene = scene->second;
		currentScene->OnEnter();
	}
}
