#include "lib/leetlib.h"
#include <math.h>

#include <vector>
#include <map>
#include <string>

int x[50];
int y[50];
int time=0;

struct bullet
{
	float BX = 0;
	float BY = 0;
	float BA = 0;
};

struct Sprite
{
	void* texture = nullptr;

	Sprite() {}
	Sprite(void* texture_) : texture(texture_) {}
	operator void* () const { return texture; }
};

bullet bullets[10];
std::map<char, Sprite> Glyphs;
Sprite Enemy;
Sprite U;
Sprite bull;
float UX = 400, UY = 550;

using namespace std::string_literals;

Sprite LoadGlyph(char glyph)
{
	std::string path = "gfx/";
	if (glyph >= 'a' && glyph <= 'z')
		path += glyph + "let.png"s;
	else if (glyph >= '0' && glyph <= '9')
		path += "num"s + glyph + ".png"s;
	else
		throw std::exception("Non-existent glyph requested");

	return LoadSprite(path.c_str());
}

void Initialize()
{
	for (char c = 'a'; c <= 'z'; ++c) {
		Glyphs[c] = LoadGlyph(c);
	}
	for (char c = '0'; c <= '9'; ++c) {
		Glyphs[c] = LoadGlyph(c);
	}
	Glyphs[' '] = {};

	// SETUP
	Enemy = LoadSprite("gfx/Little Invader.png");
	U = LoadSprite("gfx/Big Invader.png");
	bull = LoadSprite("gfx/bullet.png");
	for (int n = 0; n < 50; ++n)
	{
		x[n] = (n % 10) * 60 + 120;
		y[n] = (n / 10) * 60 + 70;
	}
}

void RenderTitle(int time)
{
	static const char title[] = "space invaders";
	for (unsigned int n = 0; n < strlen(title); ++n)
	{
		auto glyph = Glyphs[title[n]]; 
		if (glyph)	// Avoid unsupported characters
		{	
			DrawSprite(glyph, (float)(n * 40 + 150), 30, 
				20, 20, 
				(float)(sin(time * 0.1) * n * 0.01));
		}
	}
}

void RenderBullets()
{
	// Render bullets
	for (int n = 0; n < 10; ++n)
	{
		DrawSprite(bull, bullets[n].BX, bullets[n].BY -= 4, 10, 10, bullets[n].BA += 0.1f, 0xffffffff);
	}
}

void ProcessFire()
{
	// FIRE
	static int b = 0;
	static int count = 0;
	if (count) --count;
	if (!IsKeyDown(VK_SPACE)) count = 0;
	if (IsKeyDown(VK_SPACE) && count == 0)
	{ 
		bullets[b].BX = (float)UX;
		bullets[b].BY = (float)UY;
		b = (b + 1) % 10; 
		count = 15;
	}
}

void MoveAndRenderEnemies(int time)
{
	// Compute "AI"
	for (int n = 0; n < 50; ++n)
	{
		int xo = 0, yo = 0;
		int n1 = time + n * n + n * n * n;
		int n2 = time + n + n * n + n * n * n * 3;
		if (((n1 >> 6) & 0x7) == 0x7)xo += (int)((1 - cos((n1 & 0x7f) / 64.0f * 2.f * 3.141592)) * (20 + ((n * n) % 9)));
		if (((n1 >> 6) & 0x7) == 0x7)yo += (int)((sin((n1 & 0x7f) / 64.0f * 2.f * 3.141592)) * (20 + ((n * n) % 9)));
		if (((n2 >> 8) & 0xf) == 0xf)yo += (int)((1 - cos((n2 & 0xff) / 256.0f * 2.f * 3.141592)) * (150 + ((n * n) % 9)));
		DrawSprite(Enemy, (float)x[n] + xo, (float)y[n] + yo, (float)(10 + ((n) % 17)), (float)(10 + ((n) % 17)), 0, 0xffffffff);
	}
}

void Game()
{
	Initialize();

	while (true)
	{
		++time;

		if (WantQuit()) return;
		if (IsKeyDown(VK_ESCAPE)) return;

		MoveAndRenderEnemies(time);

		DrawSprite(U, UX += IsKeyDown(VK_LEFT) ? -7 : IsKeyDown(VK_RIGHT) ? 7 : 0, UY, 50, 50, (float)(3.141592 + sin(time * 0.1) * 0.1), 0xffffffff);

		ProcessFire();

		RenderBullets();

		RenderTitle(time);

		Flip();
	}
}
