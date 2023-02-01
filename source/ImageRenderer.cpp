#include "ImageRenderer.h"



ImageRenderer::ImageRenderer():Renderer()
{
	rotation = 0;
	flip = SDL_FLIP_NONE;
}

ImageRenderer::ImageRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect):Renderer(color,alpha,rotation,targetRect,sourceRect)
{
}

void ImageRenderer::Load(std::string path)
{

	RM->surface = IMG_Load(path.c_str());
	assert(RM->surface);

	SetTexture(SDL_CreateTextureFromSurface(RM->GetRenderer(), RM->surface));
	assert(GetTexture());


}

void ImageRenderer::Update()
{
	//SDL_Rect guarda int por lo tanto no funciona al utilizar deltaTime(float)

	position.x += (velocity.x);
	position.y += (velocity.y);

	targetRect.x = position.x;
	targetRect.y = position.y;

}

void ImageRenderer::Render()
{
	SDL_Point center = { targetRect.w/2,targetRect.h / 2 };
	SDL_RenderCopyEx(RM->GetRenderer(), texture, &sourceRect, &targetRect, rotation,&center, flip);

}

void ImageRenderer::SetComponents(SDL_Color color, float alpha, float rotation, SDL_Rect sourceRect)
{
	this->color = color;
	this->alpha = alpha;
	this->rotation = rotation;
	this->sourceRect = sourceRect;
}

ImageRenderer::~ImageRenderer()
{
	SDL_DestroyTexture(texture);
}

void ImageRenderer::SetSourceRect(SDL_Rect sourceRect)
{
	this->sourceRect = sourceRect;
}
