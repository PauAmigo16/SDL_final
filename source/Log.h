#pragma once
#include "GameObject.h"
class Log:public GameObject
{
private:
	Object* object;

	bool food;

public:
	Log(int lenght, Vector2 velocity, Vector2 startPosition);
	virtual ~Log() override;

	virtual void Update() override;
	virtual void Render() override;

	void SetObject(Object* object);
	void SetFood();

	virtual bool IsFood() override;
	virtual Object* GetObject();

	virtual void deleteFood() override;
};

