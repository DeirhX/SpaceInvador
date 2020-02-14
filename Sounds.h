#pragma once
#include <utility>
#include "Vector.h"

// Note: not really audio sound. Johnny Leet didn't leave us audio assets. So we're simulate them with what little we have!
class SoundEffect
{
	/*
	std::string letters;
public:
	SoundEffect(std::string sound) : letters(std::move(sound))
	{
		
	}*/
public:
	static void Play(std::string_view sound, Position position);
};

