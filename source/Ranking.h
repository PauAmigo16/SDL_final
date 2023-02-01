#pragma once
#include "Scene.h"
#include "HighScoreManager.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "TextRenderer.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

class Ranking : public Scene
{
private:
	UIButton* returnButton;

	std::vector<int> scores;
	std::vector<TextRenderer*> ranking;

public:
	Ranking();
	void ReadRanking();
	void SaveRanking();

	void SetNewScore(int score);

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

	std::string GetString(int num);

	int GetMaxScore();
	void deleteRanking();
};