#include "pch.h"
#include "Math.h"
#include "Vector.h"

float math::ToRadians(Vector2 unit_vector)
{
	return std::atan2(unit_vector.y, unit_vector.x);
}
