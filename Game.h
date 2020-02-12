#pragma once
#include "Sprites.h"
#include "vector.h"
#include "Renderables.h"
#include "Invader.h"


class Game
{
	Sprites sprites;

	Renderables<Invader> invaders;
	Renderables<Bullet> bullets;
	Player player;
	int time = 0;

public:
	Game();
	void AdvanceWorld(float delta);
	void RenderWorld();
	
	void RenderTitle(int time);
	void ProcessFire();
	void GameLoop();
};

