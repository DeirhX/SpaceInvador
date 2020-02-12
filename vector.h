#pragma once
#include <algorithm>

namespace math
{
	const float pi = 3.141592f;
	const float two_pi = 2.0f * pi;
	const float half_pi = 0.5f * pi;
}

struct Vector2
{
	float x = 0;
	float y = 0;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2 operator+ (const Vector2& other) const { return { x + other.x, y + other.y }; }
	Vector2 operator- (const Vector2& other) const { return { x - other.x, y - other.y }; }
	Vector2 operator* (float by) const { return { x * by, y * by }; }
	Vector2& operator+= (const Vector2& other) { x += other.x; y += other.y; return *this; };
	Vector2& operator-= (const Vector2& other) { x -= other.x; y -= other.y; return *this; };
};

/* Make it more clear */
using Position = Vector2;

/* Prevent mixing positions with sizes in function arguments. */
struct Size
{
	float x = 0;
	float y = 0;

	Size() = default;
	Size(float x) : x(x), y(x) {}
	Size(float x, float y) : x(x), y(y) {}
};

struct Boundary
{
	Position min;
	Position max;

	[[nodiscard]] bool IsInside(Position pos) const
	{
		return pos.x >= min.x && pos.x <= max.x
			&& pos.y >= min.y && pos.y <= max.y;
	}

	void MakeInside(Position& pos) const
	{
		pos.x = std::clamp(pos.x, min.x, max.x);
		pos.y = std::clamp(pos.y, min.y, max.y);
	}
};