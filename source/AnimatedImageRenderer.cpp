#include "AnimatedImageRenderer.h"

AnimatedImageRenderer::AnimatedImageRenderer()
{
	stopUpdate = false;

}

AnimatedImageRenderer::AnimatedImageRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect, int frameWidth, int frameHeight, int fps, bool looping): ImageRenderer(color,alpha, rotation,targetRect,sourceRect)
{
	stopUpdate = false;

}


void AnimatedImageRenderer::Update()
{
	if (!stopUpdate) 
	{
		currentFrameTime += TM->GetDeltaTime();

		currentFrame = currentFrameTime / (1/fps);

		currentAnimationFrame = currentFrame % frames;

		if (currentFrame == frames - 1 && !looping)
		{
			currentFrameTime = 0;
			stopUpdate = true;
		}
	
		sourceRect = images[currentAnimationFrame];
	}
	position.x += (velocity.x);
	position.y += (velocity.y);

	targetRect.x = position.x;
	targetRect.y = position.y;

}

void AnimatedImageRenderer::Render()
{
	SDL_Point center = { targetRect.w / 2,targetRect.h / 2 };
	SDL_RenderCopyEx(RM->GetRenderer(), texture, &sourceRect, &targetRect, rotation, &center, flip);

}

void AnimatedImageRenderer::SetImage(SDL_Rect image)
{
	images.push_back(image);
	frames = images.size();
}

void AnimatedImageRenderer::ActiveAnimation()
{
	currentFrame = TM->GetFrameIncrement();
	stopUpdate = false;

}

void AnimatedImageRenderer::SetComponents(float rotation, SDL_Rect targetRect, int fps, bool looping)
{
	position.x = targetRect.x;
	position.y = targetRect.y;
	this->rotation = rotation;
	this->targetRect = targetRect;
	this->fps = fps;
	this->looping = looping;
}
