#pragma once
#include "Renderables.h"
#include "Invader.h"
#include "Player.h"
#include "Projectile.h"

class World
{
public:
	Renderables<Invader> invaders;
	Renderables<Projectile> bullets;
	Player player;

	Boundary bounds{ Position{20, 20}, { Position{600, 400} } };
public:
	World(Player&& player) : player(player) {}
	void Advance(float delta);
	void Render();
};

World& GetWorld();