#pragma once
#include <utility>
#include "Vector.h"

// Note: not really audio sound. Johnny Leet didn't leave us audio assets. So we're simulate them with what little we have!
class SoundEffect
{
public:
	std::string_view sound;
	Position position = {};
	Vector2 speed = {};
	float duration = 25.0f;
	float spread = 0.5f;
	float spacing = 5.0f;
	float fade_start = 0;
public:
	SoundEffect(std::string_view sound, Position position, Vector2 speed = { 0, -1 }, float duration = 25.f )
		: sound(sound), position(position), speed(speed), duration(duration)
	{
	}

	static void Play(const SoundEffect& effect);
	static void Play(std::string_view sound, Position position, Vector2 speed = { 0, -1 }) { Play(SoundEffect{ sound, position, speed }); }
};

