#include "UIButton.h"

UIButton::UIButton(SDL_Rect target, std::string text)
{
	isPressed = false;
	isClicked = false;

	pos = { target.x, target.y, target.w, target.h };
	textPos = { (int)((target.x) + (target.w * 0.15f)), (int)((target.y) + (target.h * 0.15f)), (int)((float)target.w * 0.7f), (int)((target.h) * 0.7f) };
	SetTransform(target.x, target.y, target.w, target.h, 0);

	this->text = new TextRenderer({ 255,255,255 }, 255, 0, { target.x, target.y, target.w, target.h }, text);
	this->text->Load("resources/myFont.ttf");

	ImageRenderer* button = new ImageRenderer;
	button->Load("resources/Button.png");

	button->SetComponents({ 0,0,0 }, 255, 0, { 0,11,32,11 });

	button->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	button->SetScale(transform.GetScale().x, transform.GetScale().y);
	renderers.push_back(button);
}

void UIButton::Render()
{
	renderers[0]->Render();

	text->Render();

}

void UIButton::CheckCollision(Vector2 point)
{
	if (boundingBox.CheckOverlappingPoint(point))
	{
		if (IM->mousePressed)
		{
			isClicked = true;
			AM->PlayClip("Jump", 0);
		}
		else
		{
			if (isClicked)
			{
				isPressed = true;
				isClicked = false;
			}
		}
	}
	else
	{
		if (!IM->mousePressed && isClicked)
		{
			isPressed = true;
			isClicked = false;
		}

	}
}

void UIButton::SetText(std::string mesage)
{
	text->SetText(mesage);
}
