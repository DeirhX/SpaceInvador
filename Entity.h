#pragma once

enum class EntityType
{
	Player,
	PlayerProjectile,
	Invader,
	Decoration,
	World,
};

class Entity
{
	int64_t id;
	bool is_destroyed = false; // Re-use dead objects so we don't need expensive allocations and vector shifts
	float life = 100.0f;
	float life_drain = 0;
public:
	using Id = int64_t;
public:
	Entity();
	virtual ~Entity() = default;
	virtual void Destroy() { is_destroyed = true; }
	float& Life() { return life; }
	float& LifeDrain() { return life_drain; }
	[[nodiscard]] bool IsAlive() const { return !is_destroyed; }
	[[nodiscard]] bool IsDestroyed() const { return is_destroyed; }
	[[nodiscard]] virtual EntityType GetType() const = 0;

	virtual void Advance(float delta)
	{
		life -= life_drain * delta;
		if (life <= 0)
			Destroy();
	}

};

