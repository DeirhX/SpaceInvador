#pragma once
#include "Sprites.h"

class Game
{

	int x[50];
	int y[50];
	int time = 0;

	struct bullet
	{
		float BX = 0;
		float BY = 0;
		float BA = 0;
	};
	bullet bullets[10];
	float UX = 400, UY = 550;
	Sprites sprites;

public:
	Game()
	{
		// SETUP
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
			auto glyph = sprites.Glyphs[title[n]];
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
			DrawSprite(sprites.Bullet, bullets[n].BX, bullets[n].BY -= 4, 10, 10, bullets[n].BA += 0.1f, 0xffffffff);
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
			DrawSprite(sprites.Enemy, (float)x[n] + xo, (float)y[n] + yo, (float)(10 + ((n) % 17)), (float)(10 + ((n) % 17)), 0, 0xffffffff);
		}
	}

	void GameLoop()
	{
		while (true)
		{
			++time;

			if (WantQuit()) return;
			if (IsKeyDown(VK_ESCAPE)) return;

			MoveAndRenderEnemies(time);

			DrawSprite(sprites.Player, UX += IsKeyDown(VK_LEFT) ? -7 : IsKeyDown(VK_RIGHT) ? 7 : 0, UY, 50, 50, (float)(3.141592 + sin(time * 0.1) * 0.1), 0xffffffff);

			ProcessFire();

			RenderBullets();

			RenderTitle(time);

			Flip();
		}
	}
};

