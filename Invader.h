#pragma once
#include "Renderables.h"
#include "AI.h"


class Invader : public Renderable
{	using base = Renderable;
	
private:
	int seed = 0;
	float time_elapsed = 0;
	SyntheticIntelligence ai;

public:
	Invader(Sprite sprite, Position base, int seed, SyntheticIntelligence&& ai) : Renderable(sprite, base, {10}), seed(seed), ai(ai)
	{
		SetSize((float)(10 + ((seed) % 17)));
	}
	[[nodiscard]] EntityType GetType() const override { return EntityType::Invader; }
	[[nodiscard]] int GetSeed() const { return seed; };
	[[nodiscard]] Boundary GetBoundary() const override { return { Boundary{ GetLocation(), GetSize() } }; }

	void Advance(float delta) override;
	void Collide(const Entity& other) override;
	void Destroy() override;
};


