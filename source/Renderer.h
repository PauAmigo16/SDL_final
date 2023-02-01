#pragma once
#include<SDL_image.h>
#include"RenderManager.h"
#include"Vector2.h"
#include<string>
#include"TimeManager.h"

class Renderer {
protected:
	SDL_Texture* texture;
	SDL_Color color;
	float alpha;
	float rotation;
	Vector2 scale;
	Vector2 position;

	SDL_Rect targetRect;
	SDL_Rect sourceRect;
	Vector2 velocity;
public:
	Renderer();
	Renderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect);
	virtual void Load(std::string path) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	void SetColor(SDL_Color color);
	void SetAlpha(float alpha);
	void SetPosition(Vector2 position);

	void SetScale(Vector2 scale);
	void SetScale(int w, int h);

	void SetRotation(float rotation);
	SDL_Color GetColor();
	float GetAlpha();
	void SetVelocity(Vector2 v);
	SDL_Texture* GetTexture();
	void SetTexture(SDL_Texture* texture);

	virtual ~Renderer();

};
