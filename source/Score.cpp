#include "Score.h"

Score::Score()
{
	score = 0;

	text = new TextRenderer({255,255,255},255,0,{ (int)(RM->gridX / 12),(int)(RM->gridY / 4),(int)(RM->gridX*3),(int)(RM->gridY/2) }, GetString(score));
	text->Load("resources/pixelart.ttf");

	SetTransform(RM->gridX / 3, RM->gridY / 4, RM->gridX/3, RM->gridY/2, 0);



}

std::string Score::GetString(int num) {
	std::stringstream ss;

	ss << num;

	std::string str = ss.str();

	while (str.length() < 4) {
		str = "0" + str;
	}

	return str;
}

void Score::Update()
{
}

void Score::Render()
{
	text->Render();
}

void Score::AddScore(int score)
{
	this->score += score;

	text->SetText(GetString(this->score));
}

int Score::GetScore()
{
	return score;
}

void Score::SetScore(int score)
{
	this->score = score;

	text->SetText(GetString(this->score));

}

