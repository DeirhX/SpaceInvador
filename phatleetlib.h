#pragma once
#include "Sprites.h"
#include "Vector.h"

void DrawSprite(Sprite sprite, Position centre, Size size, float rotate_angle_radians = 0, DWORD tint_col_argb = 0xffffffff);
void DrawSprite(const class Renderable& renderable);


// TODO: separate file
class PerformanceTimer
{
	LARGE_INTEGER frequency = {}; // Redundant but I'm sure compiler optimizes it away
	LARGE_INTEGER last = {};
public:
	PerformanceTimer();
	float ElapsedSinceLast();
};

class Random
{
public:
	static inline std::random_device rd;
	static inline std::mt19937 generator{ rd() };
public:
	static int Next(int max);

};