#pragma once
#include "Vector.h"

enum class GameSceneId
{
	Intro,
	Gameplay,
	FirstVictory,
};

class Scene
{
protected:
	float time = 0;
public:
	virtual void Begin(class World& world) { }
	virtual void Advance(float elapsed) { time += elapsed; }
	virtual void Render() = 0;
protected:
	void RenderText(std::string_view text, Position centre, Size size, DWORD mask = 0xffffffff);
};

class IntroScene : public Scene
{
public:
	void Render() override;
};

class GameplayScene : public Scene
{
public:
	void Begin(World& world) override;
	//void Advance(float elapsed) override;
	void Render() override;
};

class FirstVictoryScene : public Scene
{
public:
	void Begin(World& world) override;
	void Render() override;
};

class Scenes
{
public:
	// This should also be solved by dynamic allocation but hey, we got just one game!
	GameSceneId active = GameSceneId::Intro;
	IntroScene intro;
	GameplayScene gameplay;
	FirstVictoryScene first_victory;
};