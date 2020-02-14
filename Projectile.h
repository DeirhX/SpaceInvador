#pragma once
#include "Renderables.h"

class Projectile : public Decoration
{
	using base = Decoration;
	
	inline const static float MaxHealth = 100.0f;

	int generation = 0; // Number of splits, used in combos
public:
	Projectile(const Sprite& sprite, const Position& base, const Size& size)
		: base(sprite, base, size)
	{
		Life() = MaxHealth;
		FadeBegin() = 10.0f;
	}

	[[nodiscard]] EntityType GetType() const override { return EntityType::PlayerProjectile; }
	[[nodiscard]] int GetGeneration() const { return generation; }
	void Collide(const Entity& other) override;
};

