#pragma once
#include "Sprites.h"
#include "Vector.h"

void DrawSprite(Sprite sprite, Position centre, Size size, float rotate_angle_radians = 0, DWORD tint_col_argb = 0xffffffff);
void DrawSprite(const class Renderable& renderable);
