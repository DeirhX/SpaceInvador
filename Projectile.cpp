#include "pch.h"
#include "Projectile.h"
#include "Math.h"
#include "Collider.h"

void Projectile::Collide(const Entity& other)
{
	EntityType otherType = other.GetType();
	if (otherType == EntityType::Invader)
	{
		Destroy();
	}
	else if (otherType == EntityType::WorldBoundary)
	{
		// Compute direction of rectangular collision (spherical surely coming in v2.0 !)
		CollisionDir dir = CollissionSolver::Direction(GetBoundary(), other.GetBoundary());
		
		switch (dir) {
		case CollisionDir::Left:
		case CollisionDir::Right:
			Speed().x *= -1.0f; 
			break;
		case CollisionDir::Top:
		case CollisionDir::Bottom:
			Speed().y *= -1.0f;
			break;
		}

		Rotation() = math::ToRadians(GetSpeed());
	}
}
