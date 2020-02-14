#pragma once
#include "World.h"
#include "Scenes.h"


class Game
{
public:
	Sprites& sprites;
	World world;
	int time = 0;

	GameplayScene sceneGameplay;
public:
	Game(Sprites& sprites);
	
	//void RenderTitle(int time);
	bool WantQuit();
	void GameLoop();
};

Game& GetGame();

