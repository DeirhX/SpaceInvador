#pragma once
#include <algorithm>
#include <cassert>

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

// Rectangular boundary for simplicity
struct Boundary
{
	Position min;
	Position max;
	Size size;

	Boundary(Position min, Position max) : min(min), max(max)
	{
		assert(min.x <= max.x);
		assert(min.y <= max.y);
	}
	Boundary(Position centre, Size size)
	{
		assert(size.x >= 0);
		assert(size.y >= 0);
		min = { centre.x - size.x / 2, centre.y - size.y / 2 };
		max = { centre.x + size.x / 2, centre.y + size.y / 2 };
	}

	[[nodiscard]] Size GetSize() { return { max.x - min.x, max.y - min.y }; }
	
	[[nodiscard]] bool IsInside(Position pos) const
	{
		return pos.x >= min.x && pos.x <= max.x
			&& pos.y >= min.y && pos.y <= max.y;
	}
	[[nodiscard]] bool Overlaps(Boundary other) const
	{
		// return !(max.x < other.min.x || min.x < other.max.x || max.y < other.min.y || min.y < other.max.y);
		if (max.x < other.min.x || min.x > other.max.x || max.y < other.min.y || min.y > other.max.y)
			return false;
		else {
			return true;
		}
	}

	void MakeInside(Position& pos) const
	{
		pos.x = std::clamp(pos.x, min.x, max.x);
		pos.y = std::clamp(pos.y, min.y, max.y);
	}
};