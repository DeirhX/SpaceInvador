#include "pch.h"
#include "World.h"
#include "PhatLeetLib.h"

void World::Advance(float delta)
{
	collider.Clear();
	ForAllRenderables([=](Renderable& r)
	{
		r.Advance(delta);
		collider.Populate(r);
	});
	collider.Solve();
}

void World::Render()
{
	ForAllRenderables([](Renderable& r)
	{
		DrawSprite(r);
	});
}

World& GetWorld()
{
	return GetGame().world;
}
