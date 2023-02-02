#pragma once
#include "GameObject.h"
class TimeBar:public GameObject
{
private:
	float startTime;
	float maxTime;
	float barSize;

public:
	TimeBar();

	virtual void Update() override;
	virtual void Render() override;

	void SetStartTime(float time);
	void SetMaxTime(float time);

	int GetPercentage();

};

