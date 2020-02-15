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

		Scene* scene = nullptr;
		do {
			switch (scenes.active)
			{
			case GameSceneId::Intro:
				scene = &scenes.intro;
				break;
			case GameSceneId::Controls:
				scene = &scenes.controls;
				break;
			case GameSceneId::IntroGameplay:
				scene = &scenes.gameplay;
				if (GetWorld().player.GetLife() == 0)
				{
					scenes.active = GameSceneId::GameOver;
					need_begin = true;
					continue;
				}
				break;
			case GameSceneId::FirstVictory:
				scene = &scenes.first_victory;
				break;
			case GameSceneId::UnlockedGameplay:
				scene = &scenes.gameplay_unlocked;
				break;
			case GameSceneId::GameOver:
				scene = &scenes.game_over;
				break;
			default:
				throw std::exception("Forgot the scene");
			}

			if (need_begin)
				scene->Begin(world);

			need_begin = false;
			scene->Advance(elapsed);
			scene->Render();

			if (scene->IsDone())
			{
				scenes.active = (GameSceneId)((int)scenes.active + 1);
				if (scenes.active == GameSceneId::End)
					scenes.active = GameSceneId::Intro;
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

int Random::Next(int max)
{
	return generator();
}
