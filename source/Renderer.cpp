#include "Renderer.h"

Renderer::Renderer()
{
	velocity = { 0,0 };
}

Renderer::Renderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect)
{
	this->color = color;
	this->alpha = alpha;
	this->rotation = rotation;
	this->targetRect = targetRect;
	this->sourceRect = sourceRect;
	velocity = { 0,0 };

}

void Renderer::SetColor(SDL_Color color)
{
	this->color = color;

}

void Renderer::SetAlpha(float alpha)
{
	this->alpha = alpha;

}

void Renderer::SetPosition(Vector2 position)
{
	this->position.x = position.x;
	this->position.y = position.y;

	this->targetRect.x = position.x;
	this->targetRect.y = position.y;


}

void Renderer::SetScale(Vector2 scale)
{
	this->targetRect.w = scale.x;
	this->targetRect.h = scale.y;
}

void Renderer::SetScale(int w, int h)
{
	this->targetRect.w = w;
	this->targetRect.h = h;
}

void Renderer::SetRotation(float rotation)
{
	this->rotation = rotation;

}

SDL_Color Renderer::GetColor()
{
	return color;
}

float Renderer::GetAlpha()
{
	return alpha;
}

void Renderer::SetVelocity(Vector2 v)
{
	velocity.x = (v.x);
	velocity.y = (v.y);

}

SDL_Texture* Renderer::GetTexture()
{
	return texture;
}

void Renderer::SetTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

Renderer::~Renderer()
{
}
