#pragma once
#include "Renderables.h"
#include "Invader.h"
#include "Projectile.h"
#include "Player.h"
#include "Collider.h"

// There can't be two skies.
class World
{
	static inline int64_t last_id = 0;
public:
	// Later move to owning pointers
	Renderables<Invader> invaders;
	Renderables<Projectile> bullets;
	Renderables<Decoration> decals;
	Player player;

	Boundary bounds{ Position{20, 20}, { Position{600, 500} } };
	Collider collider = { bounds };
public:
	World(Player&& player) : player(player) {}
	void Advance(float delta);
	void Render();
	static int64_t GetNextId()
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
		for (auto& decal: decals) unary_function(decal);
	}
};

World& GetWorld();