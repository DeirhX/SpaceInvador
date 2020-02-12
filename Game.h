#pragma once
#include "Sprites.h"
#include "vector.h"
#include "Renderables.h"


class Game
{
	Sprites sprites;

	std::vector<Invader> invaders;
	Renderables<Bullet> bullets;
	Player player;
	int time = 0;

public:
	Game();
	void RenderTitle(int time);
	void RenderBullets();
	void ProcessFire();
	void MoveAndRenderEnemies(int time);
	void GameLoop();
};

