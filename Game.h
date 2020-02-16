#pragma once
#include "World.h"
#include "Scenes.h"
#include "Score.h"


class Game
{
	static constexpr float AdvancePerSecond = 50.f;
public:
	Sprites& sprites;
	World world;
protected:
	float time = 0;
	Score score;
	
	Scenes scenes;
public:
	Game(Sprites& sprites);
	const Scenes& GetScenes() { return scenes; }
	Score& Score() { return score; }
	int AddScore(int points) { return score.Add(points); }
	int GetScore() { return score.current; }
	float& Time() { return time; }
	
	bool WantQuit();
	void GameLoop();
};

Game& GetGame();