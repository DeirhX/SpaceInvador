#include "pch.h"
#include "Decorations.h"
#include "Sounds.h"
#include "Math.h"

void Wormhole::Advance(float delta)
{
	fx_timer += delta;
	if (fx_timer > fx_tick)
	{
		fx_timer = 0;
		Vector2 offset = 25.f * math::FromRadians(Random::Next(-1.f, 1.f));
		SoundEffect::Play("ss", GetLocation() + offset, -0.2f * offset);
	}

	Rotation() += 0.1f * delta;
	base::Advance(delta);
}

void Wormhole::Collide(const Entity& other)
{
	if (other.GetType() == EntityType::Player)
	{
		activated = true;
	}
}
