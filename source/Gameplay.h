#pragma once
#include "Scene.h"
#include"Spawner.h"
#include"Frog.h"
#include "LevelLoader.h"
#include "InputManager.h"
#include "Food.h"
#include "EndPosition.h"
#include "TimeBar.h"
#include "Score.h"
#include "Lives.h"
#include "UIPanel.h"
#include "SceneManager.h"

#include<vector>
#include<map>

class Spawner;

class Gameplay :public Scene {
private:
enum GameState{
	GAMEPLAY,PAUSE,DEAD,MAPEND}
states;

	TextRenderer* text;
	void SaveScore();
	void LoadLevelFromFile(std::string path);
	float endHazardTimer;
	bool fly;
	float currentLevelTime;
	float position;
	bool lostLive;
	bool death;
	float reachEndTime;

public:		
	float levelMaxTime;
	float endHazardChances;
	
	std::map<std::string, Object*> gameUI;
	std::vector<EndPosition*> endPositions;
	std::vector<Spawner*> spawners;
	std::vector<GameObject*> tiles;
	Frog *player;
	int level;
	bool playerFood;
	Gameplay();
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	
	void SetObject(Object* object);
	void restartTime();

	void RestartLevel();
};