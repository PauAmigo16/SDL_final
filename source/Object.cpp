#include "Object.h"

Transform Object::GetTransform()
{
    return transform;
}

AABB Object::GetBoundingBox()
{
    return AABB();
}

Vector2 Object::GetVelocity()
{
    return Vector2();
}

void Object::SetPosition(Vector2 p)
{
    transform.SetPosition(p);
    boundingBox.SetTopLeft(p);
}

void Object::SetRotation(float r)
{
}

void Object::SetScale(Vector2 s)
{
}

void Object::SetVelocity(Vector2 v)
{
}

void Object::SetTransform(float x, float y, float w, float h, float rotation)
{
	transform.SetTransform(x, y, w, h, rotation);
    boundingBox.SetTopLeft({ x,y });
    boundingBox.SetSize({ w,h });


}

Object::~Object()
{
}

bool Object::GetFood()
{
    return false;
}

Object* Object::GetObject()
{
    return nullptr;
}

void Object::deleteFood()
{
}
