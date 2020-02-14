#pragma once
#include "Renderables.h"

class Invader : public Renderable
{	using base = Renderable;
	
private:
	int seed = 0;
	float time_elapsed = 0;
public:
	Invader(Sprite sprite, Position base, int seed) : Renderable(sprite, base, {10}), seed(seed)
	{
		SetSize((float)(10 + ((seed) % 17)));
	}
	EntityType GetType() const override { return EntityType::Invader; }
	
	void Advance(float delta) override;
	void Collide(const Renderable& other) override;
	void Destroy() override;
};

