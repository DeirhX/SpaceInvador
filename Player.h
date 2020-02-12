#pragma once
#include "Renderables.h"

class Player : public Renderable
{
	static inline float ShootEnergyMax = 100.0f;
	static inline float ShotCost = 25.0f;
	
	float shoot_energy = ShootEnergyMax;
	bool reloaded = true;
public:
	Player(const Sprite& sprite, const Position& base, const Size& size)
		: Renderable(sprite, base, size)
	{ }

	void Advance(float delta) override;
};

