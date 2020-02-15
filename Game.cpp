#include "pch.h"
#include "Game.h"
#include "PhatLeetLib.h"

Game::Game(Sprites& sprites) :
	sprites(sprites),
	world ({})
{
	scenes.intro.Begin(world);
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
		bool need_begin = false;
		do {
			switch (scenes.active)
			{
			case GameSceneId::Intro:
				scene = &scenes.intro;
				break;
			case GameSceneId::Controls:
				scene = &scenes.controls;
				break;
			case GameSceneId::Gameplay:
				scene = &scenes.gameplay;
				break;
			case GameSceneId::FirstVictory:
				scene = &scenes.first_victory;
				break;
			default:
				throw std::exception("Forgot the scene");
			}

			if (need_begin)
				scene->Begin(world);
			scene->Advance(elapsed);
			scene->Render();

			if (scene->IsDone())
			{
				scenes.active = (GameSceneId)((int)scenes.active + 1);
				need_begin = true;
			}

		} while (scene->IsDone());

		
		
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
