#include "pch.h"
#include "World.h"
#include "Game.h"
#include "Collider.h"
#include "Vector.h"

using FloatLimits = std::numeric_limits<float>;

World::World(Player&& player) 
	: colliders { 
		Collider { Boundary { Position { FloatLimits::lowest(), FloatLimits::lowest() }, Position { FloatLimits::max(), bounds.min.y } } },
		Collider { Boundary { Position { FloatLimits::lowest(), bounds.max.y }, Position { FloatLimits::max(), FloatLimits::max() } } },
		Collider { Boundary { Position { FloatLimits::lowest(), FloatLimits::lowest() }, Position { bounds.min.x, FloatLimits::max() } } },
		Collider { Boundary { Position { bounds.max.x, FloatLimits::lowest() }, Position { FloatLimits::max(), FloatLimits::max() } } }
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
