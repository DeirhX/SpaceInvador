#pragma once
#include "Renderables.h"
#include "Invader.h"
#include "Player.h"

class World
{
public:
	Renderables<Invader> invaders;
	Renderables<Bullet> bullets;
	Player player;

	Boundary bounds{ {20, 20}, {600, 400} };
public:
	World(Player&& player) : player(player) {}
	void Advance(float delta);
	void Render();
};

World& GetWorld();