#pragma once

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
