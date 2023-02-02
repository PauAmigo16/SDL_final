#pragma once
#include"Vector2.h"


class Transform
{
private:
	Vector2 position;
	Vector2 scale;
	float rotation;

public:
	Transform() = default;
	Transform(Vector2 position, Vector2 scale, float rotation) : position(position), scale(scale), rotation(rotation) {}

	void SetTransform(float x, float y, float w, float h, float rotation);
	void SetPosition(Vector2 p);

	Vector2 GetPosition();
	Vector2 GetScale();
	float GetRotation();
};

