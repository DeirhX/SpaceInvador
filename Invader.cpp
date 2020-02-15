#include "pch.h"
#include "Invader.h"
#include "Math.h"
#include "World.h"
#include "Sounds.h"
#include "Game.h"

void Invader::Advance(float delta)
{
	ai.Advance(delta, *this);
	base::Advance(delta);
}

void Invader::Collide(const Entity& other)
{
	if (other.GetType() == EntityType::PlayerProjectile )
	{
		auto score = 100 * (1 + ((Projectile&)other).GetGeneration());
		auto score_str = std::to_string(score);
		auto score_fx = SoundEffect{ score_str, GetProjection(), Vector2{0, 0}, 100.f };
		score_fx.spread = 0.05f;
		score_fx.spacing = 10.0f;
		score_fx.fade_start = 50.0f;
		SoundEffect::Play(score_fx);

		GetGame().Score() += score;
		Life() -= 100.f;
		Destroy();
	}
	ai.OnCollide(*this, other);
}

void Invader::Destroy()
{
	SoundEffect::Play("pow", GetProjection());

	base::Destroy();
}

