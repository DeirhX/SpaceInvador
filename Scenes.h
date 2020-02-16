#pragma once
#include "Vector.h"
#include "World.h"

enum class GameSceneId
{
	Intro,
	Controls,
	InvadersGameplay,
	FirstVictory,
	ThrustGameplay,
	ThrustVictory,
	WormholeGameplay,
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
	bool IsDone() override
	{
		return IsKeyDown(VK_SPACE);
	}
};

class IntroScene : public TextScene
{
	bool pressed = true;
public:
	void Begin(class World& world) override;
	void Render() override;
	bool IsDone() override
	{
		if (!pressed && IsKeyDown(VK_SPACE)) return true;
		if (!IsKeyDown(VK_SPACE)) pressed = false;
		return false;
	}
};

class ControlsScene : public TextScene
{
	std::string discover_text;
public:
	void Begin(World& world) override;
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

class SecondVictoryScene : public TextScene
{
public:
	void Render() override;
};

class ThrustGameplayScene : public GameplayScene
{
public:
	void Begin(World& world) override;
	bool IsDone() override
	{
		return GetWorld().invaders.Size() == 0;
	}
};

class WormholeGameplayScene : public GameplayScene
{
	Wormhole wormhole = Wormhole {  {0, 0}, {50, 40} };
public:
	void Begin(World& world) override;
	bool IsDone() override
	{
		return GetWorld().invaders.Size() == 0 || wormhole.GetActivated();
	}
};


class Scenes
{
public:
	// This should also be solved by dynamic allocation but hey, we got just one game!
	GameSceneId active = GameSceneId::Intro;
	IntroScene intro;
	ControlsScene controls;
	GameplayScene invaders_game;
	FirstVictoryScene invaders_victory;
	GameOverScene game_over;
	ThrustGameplayScene thrust_game;
	SecondVictoryScene thrust_victory;
	WormholeGameplayScene wormhole_game;

	// Ok, this is growing ugly...
	Scene& FromSceneId(GameSceneId id) 
	{
		switch (id)
		{
		case GameSceneId::Intro: return intro;
		case GameSceneId::Controls:	return controls;
		case GameSceneId::InvadersGameplay: return invaders_game;
		case GameSceneId::FirstVictory: return invaders_victory;
		case GameSceneId::ThrustGameplay: return thrust_game;
		case GameSceneId::ThrustVictory: return thrust_victory;
		case GameSceneId::WormholeGameplay: return wormhole_game;
		case GameSceneId::GameOver:return game_over;
		default: throw std::exception("Forgot the scene");
		}
	}
};