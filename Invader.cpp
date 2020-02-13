#include "pch.h"
#include "Invader.h"
#include "Math.h"

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

	Renderable::Advance(delta);
}

void Invader::Collide(Renderable& other)
{
	if (other.GetType() == EntityType::PlayerProjectile )
	{
		Life() -= 100.f;
		Destroy();
	}
}
