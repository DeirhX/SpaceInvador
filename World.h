#pragma once
#include "Renderables.h"
#include "Invader.h"
#include "Projectile.h"
#include "Player.h"
#include "Collider.h"

class World
{
	int64_t last_id = 0;
public:
	Renderables<Invader> invaders;
	Renderables<Projectile> bullets;
	Player player;

	Boundary bounds{ Position{20, 20}, { Position{600, 400} } };
	Collider collider = { bounds };
public:
	World(Player&& player) : player(player) {}
	void Advance(float delta);
	void Render();
	int64_t GetNextId()
	{
		assert(last_id >= 0); // Overflow?
		return ++last_id;
	}
private:
	template <typename TFunction> void ForAllRenderables(TFunction unary_function)
	{
		unary_function(player);
		for (auto& bullet : bullets) unary_function(bullet);
		for (auto& invader : invaders) unary_function(invader);
	}
};

World& GetWorld();