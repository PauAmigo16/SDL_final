#pragma once

#include"Renderer.h"
#include<string>
#include <cassert>
#include"TimeManager.h"

class ImageRenderer : public Renderer {
public:
	SDL_RendererFlip flip;
	ImageRenderer();
	ImageRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect);
	virtual void Load(std::string path) override;
	virtual void Update() override;
	virtual void Render() override;
	void SetComponents(SDL_Color color, float alpha, float rotation, SDL_Rect sourceRect);
	virtual ~ImageRenderer() override;
	void SetSourceRect(SDL_Rect sourceRect);
};
