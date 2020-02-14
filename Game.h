#pragma once
#include "World.h"
#include "Scenes.h"


class Game
{
	static constexpr float AdvancePerSecond = 50.f;
public:
	Sprites& sprites;
	World world;
	float time = 0;

	GameplayScene sceneGameplay;
public:
	Game(Sprites& sprites);
	
	//void RenderTitle(int time);
	bool WantQuit();
	void GameLoop();
};

Game& GetGame();


// TODO: separate file
class PerformanceTimer
{
	LARGE_INTEGER frequency = {}; // Redundant but I'm sure compiler optimizes it away
	LARGE_INTEGER last = {};
public:
	PerformanceTimer();
	float ElapsedSinceLast();
};