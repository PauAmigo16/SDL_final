#include "Tile.h"

Tile::Tile()
{
	ImageRenderer image();
	water = false;
}

void Tile::Render()
{
	for (auto render : renderers)
	{
		render->Render();
	}
}

void Tile::IsLethal(bool isLethal)
{
	this->lethal = isLethal;
}

void Tile::SetImage(SDL_Rect sourceRect)
{
	ImageRenderer* image = new ImageRenderer;
	image->Load("resources/Assetsv2.png");
	image->SetComponents({ 0,0,0 }, 255, 0, sourceRect);
	image->SetPosition(transform.GetPosition());
	image->SetScale(transform.GetScale());
	renderers.push_back(image);
}

void Tile::SetWater()
{
	water = true;
}

bool Tile::IsWater()
{
	return water;
}

