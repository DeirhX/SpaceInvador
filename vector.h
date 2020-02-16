#pragma once

struct Vector2
{
	float x = 0;
	float y = 0;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2 operator+ (Vector2 other) const { return { x + other.x, y + other.y }; }
	Vector2 operator- (Vector2 other) const { return { x - other.x, y - other.y }; }
	Vector2 operator* (float by) const { return { x * by, y * by }; }
	float operator* (Vector2 other) const { return { x * other.x + y * other.y }; }
	Vector2& operator+= (Vector2 other) { x += other.x; y += other.y; return *this; };
	Vector2& operator-= (Vector2 other) { x -= other.x; y -= other.y; return *this; };
	Vector2& operator*= (float by) { x *= by; y *= by; return *this; };
	bool operator == (Vector2 other) const { return x == other.x && y == other.y; }
	bool operator != (Vector2 other) const { return x != other.x || y != other.y; }

	float GetLength() const { return std::sqrt(x * x + y * y); }
	Vector2& Normalize()
	{
		if (x || y) 
		{
			float length = GetLength();
			x /= length;
			y /= length;
		}
		return *this;
	}
};
inline Vector2 operator* (float scalar, Vector2 vector) { return { scalar * vector.x, scalar * vector.y}; }

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
inline Vector2 operator* (float scalar, Size size) { return { scalar * size.x, scalar * size.y }; }
inline Vector2 operator+ (Vector2 vector, Size size) { return { vector.x + size.x, vector.y + size.y }; }
inline Vector2 operator- (Vector2 vector, Size size) { return { vector.x - size.x, vector.y - size.y }; }

// Rectangular boundary for simplicity
struct Boundary
{
	Position min;
	Position max;
	//Size size;

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

	[[nodiscard]] Size GetSize() const { return { max.x - min.x, max.y - min.y }; }
	[[nodiscard]] Position GetCentre() const { return min + 0.5f * GetSize(); }
	
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