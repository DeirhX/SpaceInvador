#include "pch.h"
#include "Projectile.h"
#include "Math.h"

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
		float width = 0.5f * (GetSize().x + other.GetSize().x);
		float height = 0.5f * (GetSize().y + other.GetSize().y);
		float dx = GetLocation().x - other.GetLocation().x;
		float dy = GetLocation().y - other.GetLocation().y;

		assert(abs(dx) <= width && abs(dy) <= height);

		float wy = width * dy;
		float hx = height * dx;

		if (wy > hx) {
			if (wy > -hx) 
				Speed().y *= -1.0f; // TOP collision
			else
				Speed().x *= -1.0f; // LEFT collision
		}
		else {
			if (wy > -hx)
				Speed().x *= -1.0f; // RIGHT collision
			else
				Speed().y *= -1.0f; // BOTTOM collision
		}

		Rotation() = math::ToRadians(GetSpeed());
	}
}
