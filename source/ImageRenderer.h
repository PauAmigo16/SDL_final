#pragma once

#include"Renderer.h"
#include<string>
#include <cassert>
#include"TimeManager.h"

class ImageRenderer : public Renderer {
public:
	ImageRenderer();
	ImageRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect);
	virtual ~ImageRenderer() override;

	SDL_RendererFlip flip;

	virtual void Load(std::string path) override;
	virtual void Update();
	virtual void Render() override;

	void SetComponents(SDL_Color color, float alpha, float rotation, SDL_Rect sourceRect);
	void SetSourceRect(SDL_Rect sourceRect);
};
