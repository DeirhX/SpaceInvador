#include "pch.h"
#include "Game.h"
#include "phatleetlib.h"

Game::Game() :
	player { sprites.Player, {400.f, 550.f}, {50.f} }
{
	for (int n = 0; n < 50; ++n)
	{
		invaders.Add({ sprites.Enemy,
							  Position{ (n % 10) * 60.f + 120,(n / 10) * 60.f + 70 },
							  (int)invaders.Size() });
	}
}

void Game::AdvanceWorld(float delta)
{
	player.Advance(delta);
	for (auto& bullet : bullets) bullet.Advance(delta);
	for (auto& invader: invaders) invader.Advance(delta);
}

void Game::RenderTitle(int time)
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

void Game::RenderBullets()
{
	// Render bullets
	for (auto& bullet : bullets)
	{
		DrawSprite(bullet, 0, 0xffffffff);
	}
}

void Game::ProcessFire()
{
	// FIRE
	static int b = 0;
	static int count = 0;
	if (count) --count;
	if (!IsKeyDown(VK_SPACE)) count = 0;
	if (IsKeyDown(VK_SPACE) && count == 0)
	{
		auto& bullet = bullets.Add({ sprites.Bullet, player.GetProjection(), {10} });
		bullet.Speed() = { 0, -2.5f };
		bullet.LifeDrain() = 1.0f;
		count = 15;
	}
}

void Game::MoveAndRenderEnemies(int time)
{
	// Compute "AI"
	for (int n = 0; n < 50; ++n)
	{
		DrawSprite(invaders[n], 0, 0xffffffff);
	}
}

void Game::GameLoop()
{
	while (true)
	{
		++time;

		if (WantQuit()) return;
		if (IsKeyDown(VK_ESCAPE)) return;

		MoveAndRenderEnemies(time);

		AdvanceWorld(1.0f);

		auto movement_offset = Position{ IsKeyDown(VK_LEFT) ? -7.0f : IsKeyDown(VK_RIGHT) ? 7.0f : 0, 0 };
		player.Location() += movement_offset;
		DrawSprite(player, (float)(3.141592 + sin(time * 0.1) * 0.1), 0xffffffff);

		ProcessFire();

		RenderBullets();

		RenderTitle(time);

		Flip();
	}
}