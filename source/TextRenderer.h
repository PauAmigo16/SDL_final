#pragma once
#include<SDL_ttf.h>
#include"Renderer.h"
#include<string>
#include<cassert>

class TextRenderer : public Renderer {
private:
	std::string text;
	TTF_Font* font;
public:
	TextRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, std::string text);
	void Load(std::string path) override;
	void Update() override;
	void Render() override;
	std::string GetText();
	void SetText(std::string text);




};
