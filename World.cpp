#include "pch.h"
#include "World.h"
#include "Game.h"
#include "Collider.h"
#include "Vector.h"

const float LimitMin = -10000.0f;
const float LimitMax = +10000.0f;

World::World(Player&& player) 
	: colliders { 
		Collider { Boundary { Position { LimitMin, LimitMin },	   Position { LimitMax, bounds.min.y } } },
		Collider { Boundary { Position { LimitMin, bounds.max.y }, Position { LimitMax, LimitMax } } },
		Collider { Boundary { Position { LimitMin, LimitMin },     Position { bounds.min.x, LimitMax } } },
		Collider { Boundary { Position { bounds.max.x, LimitMin }, Position { LimitMax, LimitMax } } }
	}, player(player)
{
	
}

void World::Advance(float delta)
{
	collissionSolver.Clear();
	ForAllEntities([=](Entity& r)
	{
		r.Advance(delta);
		if (r.IsAlive())
			collissionSolver.Populate(r);
	});
	collissionSolver.Solve();

	TrimEntityContainers();
}

void World::Render()
{
	ForAllEntities([](Entity& r)
	{
		r.Render();
	});
}

World& GetWorld()
{
	return GetGame().world;
}
