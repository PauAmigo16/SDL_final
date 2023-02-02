#include "Spawner.h"

Spawner::Spawner(std::string id, int maxSpawnTime, int minSpawnTime, float startPositionX, float startPositionY, int startVelocityX, int startVelocityY, bool pos) 
	: id(id), maxSpawnTime(maxSpawnTime), minSpawnTime(minSpawnTime),pos(pos)
{

	this->startPosition.x = startPositionX;
	this->startPosition.y = startPositionY;

	this->startVelocity.x = startVelocityX;
	this->startVelocity.y = startVelocityY;

	this->maxLenght = maxLenght;
	this->minLenght = minLenght;

	spawnTime =  minSpawnTime + ((((float)rand()) / (float)RAND_MAX)*(maxSpawnTime- minSpawnTime));

	if (pos)
	{
		startVelocity.x = -startVelocity.x;
	}

	rotation = 0;
}

Spawner::Spawner(std::string id, int maxSpawnTime, int minSpawnTime, float startPositionX, float startPositionY, int startVelocityX, int startVelocityY, int maxLenght, int minLenght, bool pos, int hazardChance)
	: id(id), maxSpawnTime(maxSpawnTime), minSpawnTime(minSpawnTime), maxLenght(maxLenght), minLenght(minLenght), pos(pos), hazardChance(hazardChance)
{
	this->startPosition.x = startPositionX;
	this->startPosition.y = startPositionY;

	this->startVelocity.x = startVelocityX;
	this->startVelocity.y = startVelocityY;

	spawnTime = minSpawnTime + ((((float)rand()) / (float)RAND_MAX) * (maxSpawnTime - minSpawnTime));

	if (pos)
	{
		startVelocity.x = -startVelocity.x;
	}

	rotation = 0;
}

Spawner::Spawner(std::string id, int maxSpawnTime, int minSpawnTime, float startPositionX, float startPositionY, int startVelocityX, int startVelocityY, int maxLenght, int minLenght, bool pos, int hazardChance, int snakeChance)
	: id(id), maxSpawnTime(maxSpawnTime), minSpawnTime(minSpawnTime), maxLenght(maxLenght), minLenght(minLenght), pos(pos), hazardChance(hazardChance), snakeChance(snakeChance)
{
	this->startPosition.x = startPositionX;
	this->startPosition.y = startPositionY;

	this->startVelocity.x = startVelocityX;
	this->startVelocity.y = startVelocityY;

	spawnTime = minSpawnTime + ((((float)rand()) / (float)RAND_MAX) * (maxSpawnTime - minSpawnTime));

	if (pos)
	{
		startVelocity.x = -startVelocity.x;

	}

	rotation = 0;
}

bool Spawner::Update()
{
	if (TM->GetCurrentTime() > (elapsedTime+spawnTime))
	{
		spawnTime = minSpawnTime + ((((float)rand()) / (float)RAND_MAX) * (maxSpawnTime - minSpawnTime));
		elapsedTime = TM->GetCurrentTime();
		return true;
	}

	return false;
}

void Spawner::GetObject(Gameplay* gameplay)
{
	if (id == "log")
	{
		if (rand() % 100 >= hazardChance)
		{
			lenght = rand() % minLenght + maxLenght;

			if (pos)
			{
				startPosition.x =RM->windowWidht;
			}
			else
			{
				startPosition.x = 0 - (lenght * (RM->windowWidht / 14));
			}

			Log* log = new Log(lenght,startVelocity,startPosition);
			gameplay->SetObject(log);

			if (rand() % 100 < snakeChance)
			{
				Snake* snake = new Snake(log->GetTransform().GetPosition().x, log->GetTransform().GetScale().x - ((RM->gridX*1.5f)), 0.5f, startVelocity,log->GetTransform().GetPosition());
				log->SetObject(snake);
			}
			else if(rand() % 100 < 30 && gameplay->food == false)
			{
				Food* food = new Food(log->GetTransform().GetPosition().x, log->GetTransform().GetScale().x - RM->gridX, startVelocity, log->GetTransform().GetPosition());
				log->SetObject(food);
				gameplay->food = true;
				log->SetFood();
			}
		}
		else
		{
			if (pos)
			{
				startPosition.x = RM->windowWidht;
				CrocodileMouth* crocodileMouth = new CrocodileMouth(startVelocity, startPosition, pos);
				gameplay->SetObject(crocodileMouth);

				Crocodile* crocodile = new Crocodile(startVelocity, startPosition, pos);
				gameplay->SetObject(crocodile);
			}
			else
			{
				startPosition.x = 0 - (3 * RM->gridX);
				Crocodile* crocodile = new Crocodile(startVelocity, startPosition, pos);
				gameplay->SetObject(crocodile);

				startPosition.x += (2 * RM->gridX);
				CrocodileMouth* crocodileMouth = new CrocodileMouth(startVelocity, startPosition, pos);
				gameplay->SetObject(crocodileMouth);
			}

		}
		return;

	}
	else if (id == "turtle")
	{
		if (rand() % 100 >= hazardChance)
		{
			lenght = rand() % minLenght + maxLenght;
			if (pos)
			{
				startPosition.x = RM->windowWidht;
			}
			else
			{
				startPosition.x = 0 - (lenght * (RM->windowWidht / 14));

				rotation = 180;
			}
			Turtles* turtle = new Turtles(lenght, startVelocity, startPosition, rotation);
			gameplay->SetObject(turtle);		

		}
		else
		{
			lenght = rand() % minLenght + maxLenght;
			if (pos)
			{
				startPosition.x = RM->windowWidht;
			}
			else
			{
				startPosition.x = 0 - (lenght * (RM->windowWidht / 14));

				rotation = 180;
			}
			DivingTurtles* divingTurtles = new DivingTurtles(lenght, startVelocity, startPosition, rotation);
			gameplay->SetObject(divingTurtles);
		}
		return;

	}
	else if (id == "racing0"|| id == "farming0" || id == "family0" || id == "racing1" || id == "truck0")
	{
		if (id == "truck0")
		{
			lenght = 2;
		}
		else
		{

			lenght = 1;
		}
		if (pos)
		{
			startPosition.x = RM->windowWidht;
			if (id == "racing0" || id == "truck0" || id == "family0")
			{
				rotation = 0;
			}
			else
			{
				rotation = 180;
			}
		}
		else
		{
			startPosition.x = 0 - (lenght * (RM->windowWidht / 14));
			if (id == "racing0" || id == "truck0" || id == "family0")
			{
				rotation = 180;
			}
			else
			{
				rotation = 0;
			}
		}
		Car* car = new Car(startVelocity, startPosition,id,lenght, rotation);
		gameplay->SetObject(car);
		return;

	}
	assert(0);
}
