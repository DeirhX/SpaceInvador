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
