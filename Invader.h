#pragma once
#include "Renderables.h"

class Invader : public Renderable
{
private:
	int seed = 0;
	float time_elapsed = 0;
public:
	Invader(Sprite sprite, Position base, int seed) : Renderable(sprite, base, {10}), seed(seed)
	{
		SetSize((float)(10 + ((seed) % 17)));
	}
	EntityType GetType() override { return EntityType::Player; }
	
	void Advance(float delta) override;
};

