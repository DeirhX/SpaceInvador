#pragma once
#include "Renderables.h"

class Projectile : public Renderable
{
public:
	Projectile(const Sprite& sprite, const Position& base, const Size& size)
		: Renderable(sprite, base, size)
	{
	}

	EntityType GetType() override { return EntityType::PlayerProjectile; }
};

