#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, std::string text) :Renderer(color, alpha, rotation, targetRect, sourceRect)
{
	this->color = color;
	this->alpha = alpha;
	this->rotation = rotation;

	this->targetRect = targetRect;

	this->text = text;

}

void TextRenderer::Load(std::string path)
{
	font = TTF_OpenFont(path.c_str(), 24);
	assert(font);

	RM->surface = TTF_RenderText_Solid(font, text.c_str(), color);
	assert(RM->surface);


	SetTexture(SDL_CreateTextureFromSurface(RM->GetRenderer(), RM->surface));
	assert(GetTexture());


}

void TextRenderer::Update()
{
}

void TextRenderer::Render()
{
	SDL_RenderCopy(RM->GetRenderer(), texture, NULL, &targetRect);

}

std::string TextRenderer::GetText()
{
	return std::string();
}

void TextRenderer::SetText(std::string text)
{
	this->text = text;
	RM->surface = TTF_RenderText_Solid(font, text.c_str(), color);
	assert(RM->surface);


	SetTexture(SDL_CreateTextureFromSurface(RM->GetRenderer(), RM->surface));
	assert(GetTexture());
}
