#pragma once
#include"Object.h"
#include <iostream>
#include"TimeManager.h"
#include"Log.h"
#include"Turtles.h"
#include"Car.h"
#include"Gameplay.h"
#include"Crocodile.h"
#include"CrocodileMouth.h"
#include"DivingTurtles.h"
#include"Snake.h"

class Gameplay;

class Spawner {
private:
	int maxSpawnTime;
	int minSpawnTime;
	float spawnTime;
	float elapsedTime;
	Vector2 startPosition;
	Vector2 startVelocity;
	int maxLenght;
	int minLenght;
	int lenght;
	std::string id;
	bool pos;
	int rotation;
	int hazardChance;
	int snakeChance;
public:

	 Spawner(std::string id, int maxSpawnTime, int minSpawnTime, float startPositionX, float startPositionY, int startVelocityX, int startVelocityY, bool pos);
	 Spawner(std::string id, int maxSpawnTime, int minSpawnTime, float startPositionX, float startPositionY, int startVelocityX, int startVelocityY, int maxLenght, int minLenght, bool pos, int hazardChance);
	 Spawner(std::string id, int maxSpawnTime, int minSpawnTime, float startPositionX, float startPositionY, int startVelocityX, int startVelocityY, int maxLenght, int minLenght, bool pos, int hazardChance, int snakeChance);

	 bool Update();
	 void GetObject(Gameplay *gameplay);
	 Spawner();
};