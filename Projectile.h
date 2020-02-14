#pragma once
#include "Renderables.h"

class Projectile : public Renderable
{
	inline const static float MaxHealth = 100.0f;
public:
	Projectile(const Sprite& sprite, const Position& base, const Size& size)
		: Renderable(sprite, base, size)
	{
		Life() = MaxHealth;
	}

	EntityType GetType() const override { return EntityType::PlayerProjectile; }
	void Collide(const Entity& other) override;
};

