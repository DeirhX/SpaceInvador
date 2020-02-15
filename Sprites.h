#pragma once
#include "lib/leetlib.h"

struct Sprite
{
	void* texture = nullptr;

	Sprite() {}
	Sprite(void* texture_) : texture(texture_) {}
	operator void* () const { return texture; }
};

class Sprites
{
public:
	const Sprite Enemy = LoadSprite("gfx/Little Invader.png");
	const Sprite Player = LoadSprite("gfx/Big Invader.png");
	const Sprite Bullet = LoadSprite("gfx/bullet.png");
	std::map<char, Sprite> Glyphs;

	static Sprite LoadGlyph(char glyph)
	{
		using namespace std::string_literals;
		std::string path = "gfx/";
		if (glyph >= 'a' && glyph <= 'z')
			path += glyph + "let.png"s;
		else if (glyph >= '0' && glyph <= '9')
			path += "num"s + glyph + ".png"s;
		else
			throw std::exception("Non-existent glyph requested");

		return LoadSprite(path.c_str());
	}

	Sprites()
	{
		for (char c = 'a'; c <= 'z'; ++c) {
			Glyphs[c] = LoadGlyph(c);
		}
		for (char c = '0'; c <= '9'; ++c) {
			Glyphs[c] = LoadGlyph(c);
		}
		Glyphs[' '] = {};
	}
};

Sprites& GetSprites();