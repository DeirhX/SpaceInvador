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
	GameOver,
	End,
};

class Scene
{
protected:
	float time = 0;
public:
	virtual void Begin(class World& world) { world = World{ {} }; time = 0; }
	virtual void Advance(float elapsed) { time += elapsed; }
	virtual void Render() = 0;
	virtual bool IsDone() = 0;
protected:
	void RenderText(std::string_view text, Position centre, Size size, DWORD mask = 0xffffffff);
};

class TextScene : public Scene
{
	bool pressed = true;
public:
	bool IsDone() override
	{
		if (!pressed && (IsKeyDown(VK_LBUTTON) || IsKeyDown(VK_SPACE)))
			return true;
		if (!IsKeyDown(VK_LBUTTON) && !IsKeyDown(VK_SPACE))
			pressed = false;
		return false;
	}
};

class GameOverScene : public TextScene
{
public:
	void Begin(class World& world) override { time = 0; }
	void Advance(float elapsed) override;
	void Render() override;
};

class IntroScene : public TextScene
{
public:
	void Render() override;
};

class ControlsScene : public TextScene
{
public:
	void Render() override;

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

class FirstVictoryScene : public TextScene
{
public:
	void Render() override;
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
	GameOverScene game_over;
};