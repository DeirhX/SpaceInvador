#include "pch.h"
#include "Game.h"
#include "PhatLeetLib.h"

Game::Game(Sprites& sprites) :
	sprites(sprites),
	world ({})
{
	scenes.active = GameSceneId::Intro;
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
	bool need_begin = true;

	while (!WantQuit())
	{
		auto elapsed = timer.ElapsedSinceLast() * AdvancePerSecond;
		time += elapsed;

		bool is_done = false;
		do 
		{
			Scene& scene = scenes.FromSceneId(scenes.active);

			if (need_begin)
				scene.Begin(world);

			need_begin = false;
			scene.Advance(elapsed);
			scene.Render();

			if (scenes.active != GameSceneId::GameOver &&
				GetWorld().player.IsActive() && GetWorld().player.GetLife() == 0)
			{
				scenes.active = GameSceneId::GameOver;
				need_begin = true;
				continue;
			}
			
			is_done = scene.IsDone();
			if (is_done)
			{
				if (scenes.active == GameSceneId::GameOver)
					scenes.active = GameSceneId::Intro;
				else 
					scenes.active = (GameSceneId)((int)scenes.active + 1);
				
				if (scenes.active == GameSceneId::End)
					scenes.active = GameSceneId::Intro;
				need_begin = true;
			}

		} while (is_done);

		
		
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

int Random::Next(int upper_bound)
{
	return generator() % upper_bound;
}
