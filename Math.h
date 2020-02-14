
#pragma once
struct Vector2;

namespace math
{
	const float pi = 3.141592f;
	const float two_pi = 2.0f * pi;
	const float half_pi = 0.5f * pi;

	float ToRadians(Vector2 vector);
	Vector2 FromRadians(float radians);
}
