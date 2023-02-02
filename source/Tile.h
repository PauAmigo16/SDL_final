#pragma once
#include "GameObject.h"
class Tile:public GameObject
{
private:
	bool water;
public:
	Tile();
	Tile(bool isLethal);
	virtual void Update() override {}
	virtual void Render() override;
	void IsLethal(bool isLethal);
	void SetImage(SDL_Rect sourceRect);
	void SetWater();
	bool IsWater();
};

