#pragma once
#include "Renderables.h"

class Invader : public Renderable
{	using base = Renderable;
	
private:
	int seed = 0;
	float time_elapsed = 0;
	Position transform = {};	// For temporary offsets
    
    // Cache for multiple accesses per frame (I know it's not worth it for this simple game ;)
	mutable bool pos_dirty = true;
	mutable Position projected_pos = {};

public:
	Invader(Sprite sprite, Position base, int seed) : Renderable(sprite, base, {10}), seed(seed)
	{
		SetSize((float)(10 + ((seed) % 17)));
	}
	EntityType GetType() const override { return EntityType::Invader; }

	Position& Location() { pos_dirty = true; return location; };
	Position& Transform() { pos_dirty = true; return transform; }
	[[nodiscard]] Position GetTransform() const { return transform; };
	[[nodiscard]] Position GetProjection() const override;
	[[nodiscard]] Boundary GetBoundary() const override { return { Boundary{ GetProjection(), GetSize() } }; }

	void Advance(float delta) override;
	void Collide(const Entity& other) override;
	void Destroy() override;
};

