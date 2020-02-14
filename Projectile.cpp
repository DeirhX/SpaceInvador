#include "pch.h"
#include "Projectile.h"

void Projectile::Collide(const Entity& other)
{
	EntityType otherType = other.GetType();
	if (otherType == EntityType::Invader)
	{
		Destroy();
	}
	else if (otherType == EntityType::WorldBoundary)
	{

	}
}
