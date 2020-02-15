#pragma once
#include "Renderables.h"

class Player : public Renderable
{	using base = Renderable;
	
	static inline float ShootEnergyMax = 100.0f;
	static inline float ShotCost = 25.0f;

	float shoot_energy = ShootEnergyMax;
	bool reloaded = true;
	bool active = true;

	float thrust_orientation = {}; // Last orientation before using thrusters, makes strafing less confusing
	Decoration crosshair{ GetSprites().Glyphs['o'], {}, Size{20, 15} };
public:
	Player() : Renderable(GetSprites().Player, {}, {}) { active = false; } 
	Player(const Sprite& sprite, const Position& base, const Size& size)
		: Renderable(sprite, base, size)
	{ }
	EntityType GetType() const override { return EntityType::Player; }
	
	void Advance(float delta) override;
	void Render() override;
	void Collide(const Entity& other) override;
private:
	void HandleShoot(float delta);
};


