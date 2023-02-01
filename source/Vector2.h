#pragma once

class Vector2 {
public:
	Vector2();
	Vector2(float x, float y);

	float x;
	float y;

	Vector2 operator + (Vector2 a)
	{
		return Vector2(a.x + x, a.y + y);
	}
	Vector2 operator - (Vector2 a)
	{
		return Vector2(a.x - x, a.y - y);
	}
	Vector2 operator * (float scale)
	{
		return Vector2(x * scale, y * scale);
	}
	Vector2 operator / (float scale)
	{
		return Vector2(x / scale, y / scale);
	}
	bool operator== (Vector2 a)
	{
		return (a.x == x && a.y == y);
	}
	bool operator != (Vector2 a)
	{
		return !(a.x == x && a.y == y);
	}
};