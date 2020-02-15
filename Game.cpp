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
							 (int)world.invaders.Size(), JohnnyLeetAI{n+1} });
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
	PerformanceTimer timer;
	
	while (!WantQuit())
	{
		auto elapsed = timer.ElapsedSinceLast() * AdvancePerSecond;
		time += elapsed;
		
		Scene* scene = nullptr;
		switch (active_scene)
		{
		case GameSceneId::Intro:
			scene = &scene_intro;
			if (IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_SPACE))
				active_scene = GameSceneId::Gameplay;
			else
				break;
		case GameSceneId::Gameplay:
			scene = &scene_gameplay;
			world.Advance(elapsed);
			world.Render();
			break;
		default:
			throw std::exception("Forgot the scene");
		}
		
		scene->Advance(elapsed);
		scene->Render();
		
		Flip();
	}
}

Game& GetGame()
{
	static Game game (GetSprites()); // Attempt for re-entrancy will deadlock here. A good thing. No initialization of world must refer to game.
	return game;
}

// PerformanceTimer 
PerformanceTimer::PerformanceTimer()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&last);
}

float PerformanceTimer::ElapsedSinceLast()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	LARGE_INTEGER diff;
	diff.QuadPart = now.QuadPart - last.QuadPart;
	diff.QuadPart *= 1000000; // Prevent loss of precision
	diff.QuadPart /= frequency.QuadPart;

	last = now;
	return (float)diff.QuadPart / 1000000;
}
