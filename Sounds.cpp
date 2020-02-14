#include "pch.h"
#include "Sounds.h"
#include "Vector.h"
#include "World.h"

void SoundEffect::Play(const SoundEffect& effect)
{
	auto spawn = [=](char letter, Position offset, Vector2 speed)
	{
		auto decoration = Decoration{ GetSprites().Glyphs[letter], effect.position + offset, {10.f}, speed, effect.duration };
		if (effect.fade_start > 0)
			decoration.FadeBegin() = effect.fade_start;
		GetWorld().decals.Add(decoration);
	};

	int letters = (int)effect.sound.size();
	for(int i = 0; i < letters; ++i)
	{
		spawn(effect.sound[i], 
			Vector2{ effect.spacing * (i - letters / 2), 0 }, 
			Vector2{ effect.spread * (i - letters / 2) + effect.speed.x, effect.speed.y });
	}
}
