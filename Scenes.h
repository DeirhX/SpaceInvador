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
	WormholeVictory,
	AmbushGameplay,
	AmbushVictory,
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

/*
 * Base classes
 */
class TextScene : public Scene
{
	bool pressed = true;
public:
	void Begin(World& world) override
	{
		pressed = true;
		Scene::Begin(world);
	}
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
	static void GenerateEnemiesOutsideScreen(World& world, int count, float speed_mult = 1);
	static void GenerateEnemiesAroundPoint(World& world, Boundary bounds, int count);
};


/*
 * Intro & Outro scenes
 */
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

class GameOverScene : public TextScene
{
	std::string score_text;
public:
	void Begin(class World& world) override;
	void Advance(float elapsed) override;
	void Render() override;
	bool IsDone() override
	{
		return IsKeyDown(VK_SPACE);
	}
};



/*
 * Victory scenes
 */
class FirstVictoryScene : public TextScene
{
public:
	void Begin(World& world) override;
	void Render() override;
};

class ThrustVictoryScene : public TextScene
{
public:
	void Begin(World& world) override;
	void Render() override;
};

class WormholeVictoryScene : public TextScene
{
	std::string discover_text;
public:
	void Begin(World& world) override;
	void Render() override;
};

class AmbushVictoryScene : public TextScene
{
	std::string next_wave_text;
public:
	int wave_num = 1;
	int GetInvaderCount() const { return 40 + 5 * wave_num; }
	void Begin(World& world) override;
	void Render() override;
};

/*
 * Gameplay scenes
 */

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

class AmbushGameplayScene : public GameplayScene
{
public:
	void Begin(World& world) override;
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
	GameplayScene invaders_game;
	FirstVictoryScene invaders_victory;
	GameOverScene game_over;
	ThrustGameplayScene thrust_game;
	ThrustVictoryScene thrust_victory;
	WormholeGameplayScene wormhole_game;
	WormholeVictoryScene wormhole_victory;
	AmbushGameplayScene ambush_game;
	AmbushVictoryScene ambush_victory;

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
		case GameSceneId::WormholeVictory: return wormhole_victory;
		case GameSceneId::AmbushGameplay: return ambush_game;
		case GameSceneId::AmbushVictory: return ambush_victory;
		case GameSceneId::GameOver:return game_over;
		default: throw std::exception("Forgot the scene");
		}
	}
};
