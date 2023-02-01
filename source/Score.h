#pragma once
#include "GameObject.h"
#include "TextRenderer.h"

#include <sstream>

class Score:public GameObject
{
private:
	TextRenderer* text;
	int score;

public:
	Score();

	virtual void Update() override {}
	virtual void Render() override;

	void AddScore(int score);
	void SetScore(int score);
	int GetScore();
	std::string GetString(int num);
};

