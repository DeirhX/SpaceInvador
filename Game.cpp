#include "pch.h"
#include "Game.h"
#include "PhatLeetLib.h"

Game::Game(Sprites& sprites) :
	sprites(sprites),
	world ({})
{

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
		switch (scenes.active)
		{
		case GameSceneId::Intro:
			scene = &scenes.intro;
			if (IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_SPACE)) 
			{
				scenes.active = GameSceneId::Gameplay;
				scenes.gameplay.Begin(world);
			}
			else
				break;
		case GameSceneId::Gameplay:
			scene = &scenes.gameplay;
			world.Advance(elapsed);
			world.Render();
			if (world.invaders.Size() == 0)
			{
				scenes.active = GameSceneId::FirstVictory;
				scenes.first_victory.Begin(world);
			}
			break;
		case GameSceneId::FirstVictory:
			scene = &scenes.first_victory;
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
