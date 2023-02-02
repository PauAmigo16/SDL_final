#include "UIPanel.h"
#include "UIPanel.h"

UIPanel::UIPanel(SDL_Rect target, std::string mesage)
{
	text = new TextRenderer({255,255,255},255,0,{ (int)(target.x + (target.w * 0.1f)) , (int)(target.y + (target.h * 0.05f)) , (int)(target.w*0.8f) , (int)(target.h/3) }, mesage);
	text->Load("resources/myFont.ttf");
	SetTransform(target.x, target.y, target.w, target.h, 0);

	ImageRenderer* image = new ImageRenderer;
	image->Load("resources/Panel.png");

    image->SetComponents({ 0,0,0 }, 255, 0, { 0,0,32,32 });

	image->SetPosition({ (transform.GetPosition().x), transform.GetPosition().y });
	image->SetScale(transform.GetScale().x, transform.GetScale().y);
	renderers.push_back(image);
}

void UIPanel::Render()
{
	for (auto render : renderers)
	{
		render->Render();
	}
	for (auto button : buttons)
	{
		button.second->Render();
	}
	text->Render();
}

void UIPanel::AddButton(SDL_Rect target, std::string name, std::string text)
{
	UIButton* newButton = new UIButton(target, text);

	buttons.emplace(name, newButton);
}

void UIPanel::CheckButtonCollision(Vector2 point)
{
	for (auto button : buttons)
	{
		button.second->CheckCollision(point);
	}
}

void UIPanel::StopPress()
{
	for (auto button : buttons)
	{
		button.second->isPressed = false;
	}
}

bool UIPanel::CheckIfButtonPresed(std::string name)
{
	return buttons.find(name)->second->isPressed;
}

