#include "AABB.h"

AABB::AABB()
{
}

AABB::AABB(Vector2 topLeft, Vector2 size)
{
	this->topLeft = topLeft;
	this->size = size;
}

bool AABB::CheckOverlappingAABB(const AABB* other)
{
	//Comprobar si alguna esquina esta dentro de este objeto
	//Esquina superior izquierda
	if((((topLeft.x < other->topLeft.x && other->topLeft.x < (topLeft.x + size.x))) && ((topLeft.y < other->topLeft.y && other->topLeft.y < (topLeft.y + size.y)))))
		return true;
	//Esquina superior derecha
	if ((((topLeft.x < (other->topLeft.x+other->size.x) && (other->topLeft.x + other->size.x) < (topLeft.x + size.x))) && ((topLeft.y < other->topLeft.y && other->topLeft.y < (topLeft.y + size.y)))))
		return true;
	//Esquina inferior izquierda
	if ((((topLeft.x < other->topLeft.x && other->topLeft.x < (topLeft.x + size.x))) && ((topLeft.y < (other->topLeft.y+other->size.y)&& (other->topLeft.y + other->size.y) < (topLeft.y + size.y)))))
		return true;
	//Esquina inferior derecha
	if ((((topLeft.x < (other->topLeft.x + other->size.x) && (other->topLeft.x + other->size.x) < (topLeft.x + size.x))) && ((topLeft.y < (other->topLeft.y + other->size.y) && (other->topLeft.y + other->size.y) < (topLeft.y + size.y)))))
		return true;

	return false;

}

bool AABB::CheckOverlappingPoint(Vector2 point)
{
	return (((topLeft.x < point.x) && point.x < (topLeft.x + size.x)) && ((topLeft.y < point.y) && point.y < (topLeft.y + size.y)));
}

Vector2 AABB::GetTopLeft()
{
	return topLeft;
}

Vector2 AABB::GetSize()
{
	return size;
}

void AABB::SetTopLeft(Vector2 topLeft)
{
	this->topLeft = topLeft;
}

void AABB::SetSize(Vector2 size)
{
	this->size = size;
}

Vector2 AABB::GetCenter()
{

	return {topLeft.x+(size.x/2),topLeft.y + (size.y / 2) };
}

AABB::~AABB()
{

}

