#include "pch.h"
#include "Game.h"
#include "PhatLeetLib.h"

Game::Game(Sprites& sprites) :
	sprites(sprites),
	world (Player { sprites.Player, {400.f, 550.f}, {50.f} })
{
	for (int n = 0; n < 50; ++n)
	{
		world.invaders.Add({ sprites.Enemy,
							 Position{ (n % 10) * 60.f + 120,(n / 10) * 60.f + 70 },
							 (int)world.invaders.Size() });
	}
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


bool Game::WantQuit()
{
	return 
		::WantQuit()
		|| IsKeyDown(VK_ESCAPE);
}


void Game::GameLoop()
{
	while (!WantQuit())
	{
		++time;

		world.Advance(1.0f);
		world.Render();

		RenderTitle(time);

		Flip();
	}
}

Game& GetGame()
{
	static Game game (GetSprites()); // Attempt for re-entrancy will deadlock here. A good thing. No initialization of world must refer to game.
	return game;
}