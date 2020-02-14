#pragma once
#include "World.h"


class Game
{
public:
	Sprites& sprites;
	World world;
	int time = 0;
public:
	Game(Sprites& sprites);
	
	void RenderTitle(int time);
	bool WantQuit();
	void GameLoop();
};

Game& GetGame();

