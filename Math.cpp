#include "pch.h"
#include "Math.h"
#include "Vector.h"

float math::ToRadians(Vector2 vector)
{
	//assert(unit_vector.GetLength() == 1.0f);
	return std::atan2(vector.y, vector.x);
}

Vector2 math::FromRadians(float radians)
{
	return { std::cos(radians), std::sin(radians) };
}
