#pragma once
#include "Sprites.h"
#include "vector.h"
#include "Renderables.h"
#include "Invader.h"
#include "World.h"


class Game
{
public:
	Sprites sprites;
	World world;
	int time = 0;
public:
	Game();
	
	void RenderTitle(int time);
	void ProcessInput();
	void GameLoop();
};

Game& GetGame();

