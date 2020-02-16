#pragma once
#include "Entity.h"
#include "Sprites.h"
#include "Renderables.h"


class Decoration : public Renderable
{
	using base = Renderable;
protected:
	float fade_begin = 0; // Life at which to being linearly fading out
public:
	float& FadeBegin() { return fade_begin; }

	Decoration(const Sprite& sprite, const Position& base, const Size& size, const Vector2& speed = { 0, 0 })
		: Renderable(sprite, base, size)
	{
		Speed() = speed;
	}
	Decoration(const Sprite& sprite, const Position& base, const Size& size, const Vector2& speed, float life)
		: Decoration(sprite, base, size, speed)
	{
		Life() = life;
		LifeDrain() = 1.f;
		FadeBegin() = life;
	}
	[[nodiscard]] virtual EntityType GetType() const { return EntityType::Decoration; }
	void Advance(float delta) override
	{
		base::Advance(delta);

		if (Life() < FadeBegin()) {
			tint = ((uint8_t)(255 * Life() / FadeBegin()) << 24) | (0x00ffffff & Tint());
		}
	}
};

class Wormhole : public Decoration
{
	float fx_timer = 0;
	static constexpr float fx_tick = 1.0f;
	bool activated = false;
public:
	Wormhole(const Position& base, const Size& size)
		: Decoration(GetSprites().Glyphs['o'], base, size)
	{
		Tint() = 0x44ffffff;
	}

	[[nodiscard]] virtual EntityType GetType() const { return EntityType::Wormhole; }
	void Advance(float delta) override;
	void Collide(const Entity& other) override;
	bool GetActivated() { return activated; }

private:
	using base = Decoration;
public:
	
};
