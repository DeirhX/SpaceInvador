#include "pch.h"
#include "World.h"
#include "PhatLeetLib.h"

void World::Advance(float delta)
{
	player.Advance(delta);
	for (auto& bullet : bullets) bullet.Advance(delta);
	for (auto& invader : invaders) invader.Advance(delta);
}

void World::Render()
{
	DrawSprite(player);
	for (auto& bullet : bullets) DrawSprite(bullet);
	for (auto& invader : invaders) DrawSprite(invader);
}

World& GetWorld()
{
	return GetGame().world;
}
