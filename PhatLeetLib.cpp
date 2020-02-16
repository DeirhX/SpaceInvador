#include "pch.h"
#include "PhatLeetLib.h"
#include "Renderables.h"
#include "Sprites.h"

void DrawSprite(Sprite sprite, Position centre, Size size, float rotate_angle_radians, DWORD tint_col_argb)
{
	DrawSprite(sprite, centre.x, centre.y, size.x, size.y, rotate_angle_radians, tint_col_argb);
}

void DrawSprite(const Renderable& renderable)
{
	DrawSprite(renderable.GetSprite(), renderable.GetProjection(), renderable.GetSize(), -renderable.GetRotation(), renderable.GetTint());
}

// PerformanceTimer 
PerformanceTimer::PerformanceTimer()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&last);
}

float PerformanceTimer::ElapsedSinceLast()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	LARGE_INTEGER diff;
	diff.QuadPart = now.QuadPart - last.QuadPart;
	diff.QuadPart *= 1000000; // Prevent loss of precision
	diff.QuadPart /= frequency.QuadPart;

	last = now;
	return (float)diff.QuadPart / 1000000;
}

int Random::Next(int upper_bound)
{
	return generator() % upper_bound;
}

float Random::Next(float upper_bound)
{
	std::uniform_real_distribution<float> dist(0, upper_bound);
	return dist(generator);
}

float Random::Next(float lower_bound, float upper_bound)
{
	std::uniform_real_distribution<float> dist(lower_bound, upper_bound);
	return dist(generator);
}