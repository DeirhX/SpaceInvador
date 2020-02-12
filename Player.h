#pragma once
#include "Renderables.h"

class Player : public Renderable
{
public:
	Player(const Sprite& sprite, const Position& base, const Size& size)
		: Renderable(sprite, base, size)
	{ }

	void Advance(float delta) override;
};

