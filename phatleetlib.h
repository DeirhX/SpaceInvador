#pragma once
#include "Sprites.h"
#include "vector.h"
#include "Game.h"
#include "Renderables.h"

inline void DrawSprite(Sprite sprite, Position centre, Size size,  float rotate_angle_radians = 0, DWORD tint_col_argb = 0xffffffff)
{
	DrawSprite(sprite, centre.x, centre.y, size.x, size.y, rotate_angle_radians, tint_col_argb);
}

inline void DrawSprite(const Renderable& renderable, float rotate_angle_radians = 0, DWORD tint_col_argb = 0xffffffff)
{
	DrawSprite(renderable.GetSprite(), renderable.GetProjection(), renderable.GetSize(), renderable.GetRotation(), renderable.GetTint());
}
