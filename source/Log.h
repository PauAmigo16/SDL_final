#pragma once
#include "GameObject.h"
class Log:public GameObject
{
private:
	Object* object;
	bool food;
public:
	Log(int lenght, Vector2 velocity, Vector2 startPosition);
	virtual void Update() override;
	virtual void Render() override;
	void SetObject(Object* object);
	virtual ~Log() override;
	virtual bool GetFood() override;
	void SetFood();
	virtual Object* GetObject();
	virtual void deleteFood() override;

};

