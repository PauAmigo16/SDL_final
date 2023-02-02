#include "Transform.h"

void Transform::SetTransform(float x, float y, float w, float h, float rotation)
{
	this->position.x = x;
	this->position.y = y;

	this->scale.x = w;
	this->scale.y = h;

	this->rotation = rotation;
}

Vector2 Transform::GetPosition()
{
	return position;
}

Vector2 Transform::GetScale()
{
	return scale;
}

float Transform::GetRotation()
{
	return rotation;
}

void Transform::SetPosition(Vector2 p)
{
	position = p;
}
