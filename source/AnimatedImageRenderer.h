#pragma once
#pragma once

#include"ImageRenderer.h"
#include<string>
#include<vector>

class AnimatedImageRenderer : public ImageRenderer {
private:
	int frames;
	float fps;
	bool looping;
	int currentFrame;
	float currentFrameTime;
	int currentAnimationFrame;

	bool stopUpdate;
	std::vector<SDL_Rect> images;
public:
	AnimatedImageRenderer();
	AnimatedImageRenderer(SDL_Color color, float alpha, float rotation, SDL_Rect targetRect, SDL_Rect sourceRect, int frameWidth,int frameHeight, int fps, bool looping);
	virtual void Update() override;
	virtual void Render() override;
	void SetImage(SDL_Rect image);
	void ActiveAnimation();
	void SetComponents(float rotation, SDL_Rect targetRect, int fps, bool looping);
};
