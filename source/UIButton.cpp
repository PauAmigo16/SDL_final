#include "UIButton.h"

UIButton::UIButton(SDL_Rect target, std::string text)
{
	InMousePos = false;
	Pressed = false;
	isClicked = false;
	pos = { target.x, target.y, target.w, target.h };
	textPos = { (int)((target.x) + (target.w * 0.15f)), (int)((target.y) + (target.h * 0.15f)), (int)((float)target.w * 0.7f), (int)((target.h) * 0.7f)};
	SetTransform(target.x, target.y, target.w, target.h, 0);
	this->text = new TextRenderer({255,255,255},255,0,{ target.x, target.y, target.w, target.h },text);
	this->text->Load("resources/pixelart.ttf");

	ImageRenderer* button = new ImageRenderer;
	button->Load("resources/Button.png");

	button->SetComponents({ 0,0,0 }, 255, 0, { 0,11,32,11 });

	button->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	button->SetScale(transform.GetScale().x, transform.GetScale().y);
	renderer.push_back(button);



	ImageRenderer* buttonPressed = new ImageRenderer;
	buttonPressed->Load("resources/OnButton.png");

	buttonPressed->SetComponents({ 0,0,0 }, 255, 0, { 0,11,32,11 });

	buttonPressed->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	buttonPressed->SetScale(transform.GetScale().x, transform.GetScale().y);
	renderer.push_back(buttonPressed);
}

void UIButton::Update()
{

}

void UIButton::Render()
{
	if(!InMousePos)
		renderer[0]->Render();
	else
	{
		renderer[1]->Render();
	}

	if (isClicked)
	{
		renderer[0]->SetPosition({ (float)(pos.x + (pos.w / 4)), (float)(pos.y + (pos.h / 4))});
		renderer[0]->SetScale({ (float)(pos.w/2), (float)(pos.h/2) });

		renderer[1]->SetPosition({ (float)(pos.x + (pos.w / 4)), (float)(pos.y + (pos.h / 4)) });
		renderer[1]->SetScale({ (float)(pos.w / 2), (float)(pos.h / 2) });

		text->SetPosition({ (float)(textPos.x + (textPos.w / 4)), (float)(textPos.y + (textPos.h / 4)) });
		text->SetScale({ (float)(textPos.w / 2), (float)(textPos.h / 2) });

	}
	else
	{
		renderer[0]->SetPosition({ (float)pos.x, (float)pos.y });
		renderer[0]->SetScale({ (float)pos.w, (float)pos.h });

		renderer[1]->SetPosition({ (float)pos.x, (float)pos.y });
		renderer[1]->SetScale({ (float)pos.w, (float)pos.h });

		text->SetPosition({ (float)textPos.x, (float)textPos.y });
		text->SetScale({ (float)textPos.w, (float)textPos.h });
	}
	
	text->Render();

}

void UIButton::ComproveCollision(Vector2 point)
{
	if (boundingBox.CheckOverlappingPoint(point))
	{
		InMousePos = true;
		if (IM->mousePressed)
		{
			isClicked = true;
			AM->PlayClip("Jump",0);
		}
		else
		{
			if (isClicked)
			{
				Pressed = true;
				isClicked = false;

			}
		}

	}
	else
	{
		InMousePos = false;

		if (!IM->mousePressed && isClicked)
		{
			Pressed = true;
			isClicked = false;
		}

	}
}

void UIButton::SetText(std::string mesage)
{
	text->SetText(mesage);
}
