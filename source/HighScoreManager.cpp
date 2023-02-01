#include "HighScoreManager.h"

HighscoreManager::HighscoreManager()
{
}

HighscoreManager* HighscoreManager::GetInstance()
{
	return nullptr;
}

void HighscoreManager::LoadScores(std::string path)
{
}

void HighscoreManager::SaveScores(std::string path)
{
}

void HighscoreManager::AddScore(int value, std::string name)
{
}

std::map<int, std::string> HighscoreManager::GetScores()
{
	return std::map<int, std::string>();
}
