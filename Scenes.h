#pragma once
#include "Vector.h"
#include "World.h"

enum class GameSceneId
{
	Intro,
	Controls,
	IntroGameplay,
	FirstVictory,
	UnlockedGameplay,
	End,
};

class Scene
{
protected:
	float time = 0;
public:
	virtual void Begin(class World& world) { }
	virtual void Advance(float elapsed) { time += elapsed; }
	virtual void Render() = 0;
	virtual bool IsDone() = 0;
protected:
	void RenderText(std::string_view text, Position centre, Size size, DWORD mask = 0xffffffff);
};

class IntroScene : public Scene
{
public:
	void Render() override;
	bool IsDone() override
	{
		return IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_SPACE);
	}
};

class ControlsScene : public Scene
{
	bool pressed = true;
public:
	void Render() override;
	bool IsDone() override
	{
		if (!pressed && (IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_SPACE)))
			return true;
		if (!IsKeyDown(VK_LBUTTON) && !IsKeyDown(VK_SPACE))
			pressed = false;
		return false;
	}
};

class GameplayScene : public Scene
{
public:
	void Begin(World& world) override;
	void Advance(float elapsed) override;
	void Render() override;
	bool IsDone() override
	{
		return GetWorld().invaders.Size() == 0;
	}
};

class FirstVictoryScene : public Scene
{
public:
	void Begin(World& world) override;
	void Render() override;
	bool IsDone() override
	{
		return IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_SPACE);
	}
};

class UnlockedGameplayScene : public GameplayScene
{
public:
	void Begin(World& world) override;
	//void Render() override;
	bool IsDone() override
	{
		return GetWorld().invaders.Size() == 0;
	}
};

class Scenes
{
public:
	// This should also be solved by dynamic allocation but hey, we got just one game!
	GameSceneId active = GameSceneId::Intro;
	IntroScene intro;
	ControlsScene controls;
	GameplayScene gameplay;
	FirstVictoryScene first_victory;
	UnlockedGameplayScene gameplay_unlocked;
};