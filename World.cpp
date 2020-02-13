#include "pch.h"
#include "World.h"
#include "Game.h"

void World::Advance(float delta)
{
	collider.Clear();
	ForAllRenderables([=](Renderable& r)
	{
		r.Advance(delta);
		if (r.IsAlive())
			collider.Populate(r);
	});
	collider.Solve();
}

void World::Render()
{
	ForAllRenderables([](Renderable& r)
	{
		r.Render();
	});
}

World& GetWorld()
{
	return GetGame().world;
}
