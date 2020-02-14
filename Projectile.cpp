#include "pch.h"
#include "Projectile.h"

void Projectile::Collide(const Renderable& other)
{
	EntityType otherType = other.GetType();
	if (otherType == EntityType::Invader)
	{
		Destroy();
	}
	else if (otherType == EntityType::World)
	{

	}
}
