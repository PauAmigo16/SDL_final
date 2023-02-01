#pragma once
#include <map>
#include <iostream>

class HighscoreManager
{
private:
	static HighscoreManager* instance;
	HighscoreManager();
public:
	std::map<int, std::string> scores;

	HighscoreManager* GetInstance();
	void LoadScores(std::string path);
	void SaveScores(std::string path);
	void AddScore(int value, std::string name);
	std::map<int, std::string> GetScores();

};
