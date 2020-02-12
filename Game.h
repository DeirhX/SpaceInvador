#pragma once
#include "Sprites.h"
#include "vector.h"
#include "Renderables.h"


class Game
{
	Sprites sprites;

	std::vector<Invader> invaders;
	Player player;
	int time = 0;

	struct bullet
	{
		float BX = 0;
		float BY = 0;
		float BA = 0;
	};
	bullet bullets[10];

public:
	Game();
	void RenderTitle(int time);
	void RenderBullets();
	void ProcessFire();
	void MoveAndRenderEnemies(int time);
	void GameLoop();
};

