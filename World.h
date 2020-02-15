#pragma once
#include "Entity.h"
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
	Boundary bounds{ Position{10, 10}, { Position{800, 550} } };

	// Later move to owning pointers
	Renderables<Invader> invaders;
	Renderables<Projectile> bullets;
	Renderables<Decoration> decals;
	std::array<Collider, 4> colliders;
	Player player;

	CollissionSolver collissionSolver = { bounds };
public:
	World(Player&& player);
	Boundary GetBoundary() { return bounds; }
	void Advance(float delta);
	void Render();
	static int64_t GetNextId()
	{
		assert(last_id >= 0); // Overflow?
		return ++last_id;
	}
private:
	template <typename TFunction> void ForAllEntities(TFunction unary_function)
	{
		unary_function(player);
		for (auto& bullet : bullets) unary_function(bullet);
		for (auto& invader : invaders) unary_function(invader);
		for (auto& decal: decals) unary_function(decal);
		for (auto& collider: colliders) unary_function(collider);
	}

	void TrimEntityContainers()
	{
		invaders.Shrink();
		bullets.Shrink();
		decals.Shrink();
	}
};

World& GetWorld();