#pragma once

#include "Vector.h"

enum class EntityType
{
	Player,
	PlayerProjectile,
	Invader,
	Decoration,
	WorldBoundary,
};

class Entity
{
protected:
	int64_t id;
	bool is_destroyed = false; // Re-use dead objects so we don't need expensive allocations and vector shifts
	float life = 100.0f;
	float life_drain = 0;
	Position location;			// True origin in world, object's centre
	Size size = { 10.f, 10.f }; // Size of entity 
public:
	using Id = int64_t;
public:
	Entity(Position base, Size size);
	virtual ~Entity() = default;
	virtual void Destroy() { is_destroyed = true; }
	float& Life() { return life; }
	float& LifeDrain() { return life_drain; }
	[[nodiscard]] bool IsAlive() const { return !is_destroyed; }
	[[nodiscard]] bool IsDestroyed() const { return is_destroyed; }

	[[nodiscard]] virtual EntityType GetType() const = 0;

	Position& Location() { return location; }
	void SetSize(float newSize) { size = { newSize, newSize }; }
	void SetSize(Size newSize) { size = newSize; }
	void SetBoundary(Boundary bounds) {  location = bounds.min + 0.5f * bounds.size; }
	[[nodiscard]] Size GetSize() const { return size; }
	[[nodiscard]] Position GetLocation() const { return location; };
	[[nodiscard]] virtual Position GetProjection() const { return location; } // Support for modifying projection of position to screen in derived classes
	[[nodiscard]] virtual Boundary GetBoundary() const { return { Boundary{ GetLocation(), GetSize() } }; }
	virtual void Collide(const Entity& other) {}

	virtual void Advance(float delta)
	{
		life -= life_drain * delta;
		if (life <= 0)
			Destroy();
	}
	virtual void Render() { }
};

