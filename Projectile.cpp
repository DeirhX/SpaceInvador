#include "pch.h"
#include "Projectile.h"
#include "Math.h"
#include "Collider.h"
#include "World.h"

void Projectile::Collide(const Entity& other)
{
	EntityType otherType = other.GetType();
	if (otherType == EntityType::Invader)
	{
		auto spawn_bullet = [this](float angle)
		{
			Projectile proj{ *this };
			proj.Speed() = GetSpeed().GetLength() * math::FromRadians(Rotation() + angle);
			//proj.Life() = std::min(proj.GetLife(),50.0f);
			proj.Rotation() = math::ToRadians(proj.GetSpeed());
			++proj.generation;
			GetWorld().bullets.Add(proj);
		};
		// Split into two more bullets
		spawn_bullet(0.2f * math::pi);
		spawn_bullet(-0.2f * math::pi);
		
		Destroy();
	}
	else if (otherType == EntityType::WorldBoundary)
	{
		// Compute direction of rectangular collision (spherical surely coming in v2.0 !)
		CollisionDir dir = CollissionSolver::Direction(GetBoundary(), other.GetBoundary());
		switch (dir) { // Abort if we're already heading the right direction
		case CollisionDir::Left:  if (Speed().x >= 0) return; Speed().x *= -1.0f; break;
		case CollisionDir::Right: if (Speed().x <= 0) return; Speed().x *= -1.0f; break;
		case CollisionDir::Top:   if (Speed().y >= 0) return; Speed().y *= -1.0f; break;
		case CollisionDir::Bottom:if (Speed().y <= 0) return; Speed().y *= -1.0f; break;
		}
		
		Rotation() = math::ToRadians(GetSpeed());
	}
}
