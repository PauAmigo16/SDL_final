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
	virtual void Update() override;
	virtual void Render() override;
	void AddScore(int score);
	int GetScore();
	void SetScore(int score);
	std::string GetString(int num);
};

