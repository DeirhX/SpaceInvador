#pragma once
#include "Renderables.h"
#include "Decorations.h"

class Player : public Renderable
{	using base = Renderable;
	
	static inline float ShootEnergyMax = 100.0f;
	static inline float ShotCost = 25.0f;

	bool reloaded = true;
	bool active = true;
	float shoot_energy = ShootEnergyMax;
	float thrust_orientation = {}; // Last orientation before using thrusters, makes strafing less confusing
	float thrust_fx_timer = 0;
	static constexpr float thrust_fx_tick = 2.0f;
	Decoration crosshair{ GetSprites().Glyphs['o'], {}, Size{20, 15} };
public:
	Player() : Renderable(GetSprites().Player, {}, {}) { active = false; } 
	Player(const Sprite& sprite, const Position& base, const Size& size)
		: Renderable(sprite, base, size)
	{ }
	EntityType GetType() const override { return EntityType::Player; }
	bool IsActive() const { return active; }
	
	void Advance(float delta) override;
	void Render() override;
	void Collide(const Entity& other) override;
private:
	void HandleShoot(float delta);
	void HandleMovement(float delta);
};

