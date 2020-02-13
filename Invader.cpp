#include "pch.h"
#include "Invader.h"
#include "Math.h"
#include "World.h"

void Invader::Advance(float delta)
{
	time_elapsed += delta;
	int xo = 0, yo = 0;
	int n1 = (int)time_elapsed + seed * seed + seed * seed * seed;
	int n2 = (int)time_elapsed + seed + seed * seed + seed * seed * seed * 3;
	if (((n1 >> 6) & 0x7) == 0x7)xo += (int)((1 - cos((n1 & 0x7f) / 64.0f * math::two_pi)) * (20 + ((seed * seed) % 9)));
	if (((n1 >> 6) & 0x7) == 0x7)yo += (int)((sin((n1 & 0x7f) / 64.0f * math::two_pi)) * (20 + ((seed * seed) % 9)));
	if (((n2 >> 8) & 0xf) == 0xf)yo += (int)((1 - cos((n2 & 0xff) / 256.0f * math::two_pi)) * (150 + ((seed * seed) % 9)));
	Transform() = { (float)xo, (float)yo };

	base::Advance(delta);
}

void Invader::Collide(Renderable& other)
{
	if (other.GetType() == EntityType::PlayerProjectile )
	{
		Life() -= 100.f;
		Destroy();
	}
}

void Invader::Destroy()
{
	auto such = Vector2{ -1, -1 }.Normalize();
	auto nice  = Vector2{ 0, -1 }.Normalize();
	auto directions = Vector2{ +1, -1 }.Normalize();

	GetWorld().decals.Add(Decoration{ GetSprites().Glyphs['p'], GetProjection() + Vector2{-5.f, 0}, {10.f} , such, 10.f });
	GetWorld().decals.Add(Decoration{ GetSprites().Glyphs['o'], GetProjection() + Vector2{0, 0}, {10.f} , nice, 10.f });
	GetWorld().decals.Add(Decoration{ GetSprites().Glyphs['w'], GetProjection() + Vector2{5.f, 0}, {10.f} , directions, 10.f });
	
	base::Destroy();
}
