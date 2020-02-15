#pragma once
#include "World.h"
#include "Scenes.h"


class Game
{
	static constexpr float AdvancePerSecond = 50.f;
public:
	Sprites& sprites;
	World world;
protected:
	float time = 0;
	int score = 0;
	
	Scenes scenes;
public:
	Game(Sprites& sprites);

	int& Score() { return score; }
	float& Time() { return time; }
	
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