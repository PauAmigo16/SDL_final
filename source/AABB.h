#pragma once
#include"Vector2.h"
#include"RenderManager.h"

class AABB {
private:
	Vector2 topLeft;
	Vector2 size;
public:
	AABB();
	AABB(Vector2 topLeft, Vector2 size);
	bool CheckOverlappingAABB(const AABB* other); 
	bool CheckOverlappingPoint(Vector2 point);
	Vector2	GetTopLeft();
	Vector2 GetSize();
	void SetTopLeft(Vector2 size);
	void SetSize(Vector2 size); 
	Vector2 GetCenter();
	~AABB();

};