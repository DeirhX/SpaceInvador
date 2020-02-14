#pragma once
#include "World.h"
#include "Scenes.h"

enum class GameSceneId
{
	Intro,
	Gameplay,
};

class Game
{
	static constexpr float AdvancePerSecond = 50.f;
public:
	Sprites& sprites;
	World world;
protected:
	float time = 0;
	int score = 0;
	GameSceneId active_scene = GameSceneId::Intro;
	IntroScene scene_intro;
	GameplayScene scene_gameplay;
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