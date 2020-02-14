#include "pch.h"
#include "Sounds.h"
#include "Vector.h"
#include "World.h"

void SoundEffect::Play(std::string_view sound, Position position)
{
	constexpr float life = 25.f;

	auto spawn = [=](char letter, Position offset, Vector2 speed)
	{
		GetWorld().decals.Add(Decoration{ GetSprites().Glyphs[letter], position + offset, {10.f}, speed, life });
	};

	int letters = (int)sound.size();
	for(int i = 0; i < letters; ++i)
	{
		spawn(sound[i], Vector2{ 5.0f * (i - letters / 2), 0 }, Vector2{ 0.5f * (i - letters / 2), -1 });
	}
}
