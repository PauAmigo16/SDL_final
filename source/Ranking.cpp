#include "Ranking.h"

Ranking::Ranking()
{

	returnButton = new UIButton({
		(int) (RM->windowWidht/20),
		(int) (RM->windowHeight/20), 
		(int) (RM->windowWidht/6), 
		(int) (RM->windowHeight/15) 
		}, "Return Menu");

	for (int i = 0; i < 10; i++)
	{
		int score = 0;

		SDL_Color color;

		if (i < 3)
			color = { 0,255,0 };
		else if (i >= 3 && i < 6)
			color = { 255,255,0 };
		else 
			color = { 255,0,0};

		std::string space = "   ";
		if (i == 9)
		{
			space = " ";
		}

		TextRenderer* text = new TextRenderer(color,255,0,{
			(int)((RM->windowWidht/4)),
			(int)((RM->windowHeight/10)+ (RM->windowHeight / 10)*(0.8f*i)),
			(int)((RM->windowWidht / 2)),
			(int)((RM->windowHeight / 10)*0.8f)
			}, std::to_string((i+1)) + space + GetString(score));

		text->Load("resources/pixelart.ttf");

		scores.push_back(score);
		ranking.push_back(text);
	}
	//deleteRanking();
	ReadRanking();

}

void Ranking::ReadRanking()
{
	std::ifstream MyFileIn("resources/binary/ranking.file", std::ios::in | std::ifstream::binary);

	assert(MyFileIn);

	scores.resize(0);

	for (int i = 0; i < 10; i++)
	{
		int score;
		MyFileIn.read(reinterpret_cast<char*>(&score), sizeof(int));

		scores.push_back(score);

		if (i != 9)
			ranking[i]->SetText(std::to_string(i+1) + "   " + GetString(score));
		else
			ranking[i]->SetText(std::to_string(i + 1) + " " + GetString(score));

	}
	MyFileIn.close();

}

void Ranking::SaveRanking()
{
	std::ofstream myFile("resources/binary/ranking.file", std::ios::out | std::ofstream::binary | std::ios::trunc);

	assert(myFile);

	for (auto score : scores)
	{
		
		myFile.write(reinterpret_cast<char*>(&score), sizeof(int));

	}

	myFile.close();
}

void Ranking::SetNewScore(int score)
{
	int pos = 10;

	for (int i = 9; i >= 0; i--)
	{
		if (scores[i] < score)
		{
			pos = i;
		}
	}

	if (pos != 10)
	{
		for (int i = 9; i > pos; i--)
		{
			scores[i] = scores[i - 1];
		}
		scores[pos] = score;

	}

	SaveRanking();
}

void Ranking::Update()
{
	returnButton->ComproveCollision({ (float)IM->GetMouseX(),(float)IM->GetMouseY() });

	if (returnButton->Pressed) {
		SM->SetScene("mainMenu");
		returnButton->Pressed = false;
	}


}

void Ranking::Render()
{
	returnButton->Render();

	for (auto scores : ranking)
	{
		scores->Render();
	}
}

void Ranking::OnEnter()
{
	ReadRanking();
}

void Ranking::OnExit()
{
}

std::string Ranking::GetString(int num) {
	std::stringstream ss;

	ss << num;

	std::string str = ss.str();

	while (str.length() < 4) {
		str = "0" + str;
	}

	return str;
}

int Ranking::GetMaxScore()
{
	return scores[0];
}

void Ranking::deleteRanking()
{
	for (int i = 9; i >= 0; i--)
	{
		scores[i] = 0;
	}
	SaveRanking();
}
