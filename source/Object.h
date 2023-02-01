#pragma once
#include"AABB.h"
#include"Transform.h"

class Object {
public:
	Transform transform;
	AABB boundingBox;
	Vector2 velocity;
	bool getDamage;
	Object() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;
	Transform GetTransform();
	AABB GetBoundingBox();
	Vector2 GetVelocity();
    virtual void SetPosition(Vector2 p);
	void SetRotation(float r);
	void SetScale(Vector2 s);
	void SetVelocity(Vector2 v);
	virtual void SetTransform(float x, float y, float w, float h, float rotation);
	virtual ~Object();
	virtual bool GetFood();
	virtual Object* GetObject();
	virtual void deleteFood();


};
