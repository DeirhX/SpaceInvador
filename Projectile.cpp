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
		BouncyAI::OnCollide(*this, other);
		
		Rotation() = math::ToRadians(GetSpeed());
	}
}
