#pragma once
#include"Vector2.h"


class Transform
{
public:
	Transform();
	Transform(Vector2 position,	Vector2 scale,	float rotation);
	void SetTransform(float x, float y, float w, float h, float rotation);
	Vector2 GetPosition();
	Vector2 GetScale();
	float GetRotation();

	void SetPosition(Vector2 p);
	~Transform();
private:
	Vector2 position;
	Vector2 scale;
	float rotation;

};

