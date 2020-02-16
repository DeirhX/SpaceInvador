#include "pch.h"
#include "Game.h"
#include "PhatLeetLib.h"

Game::Game(Sprites& sprites) :
	sprites(sprites),
	world ({})
{
	scenes.active = GameSceneId::ThrustVictory;
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
				else if (scenes.active == GameSceneId::AmbushVictory )
					scenes.active = GameSceneId::AmbushGameplay; // Give us more money to develop more
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

