#include "pch.h"
#include "AI.h"
#include "Math.h"
#include "Invader.h"
#include "Collider.h"


void JohnnyLeetAI::Advance(float delta, Renderable& invader)
{
	// Master's work. This is great. And I mean it.
	// Do Not Touch.
	time_elapsed += delta;
	int xo = 0, yo = 0;
	int n1 = (int)time_elapsed + seed * seed + seed * seed * seed;
	int n2 = (int)time_elapsed + seed + seed * seed + seed * seed * seed * 3;
	if (((n1 >> 6) & 0x7) == 0x7)xo += (int)((1 - cos((n1 & 0x7f) / 64.0f * math::two_pi)) * (20 + ((seed * seed) % 9)));
	if (((n1 >> 6) & 0x7) == 0x7)yo += (int)((sin((n1 & 0x7f) / 64.0f * math::two_pi)) * (20 + ((seed * seed) % 9)));
	if (((n2 >> 8) & 0xf) == 0xf)yo += (int)((1 - cos((n2 & 0xff) / 256.0f * math::two_pi)) * (150 + ((seed * seed) % 9)));

	invader.Speed() =  8.f * Vector2{ (float)(xo - last_xo), (float)(yo - last_yo) };

	last_xo = xo;
	last_yo = yo;
}

void BouncyAI::Advance(float delta, Renderable& invader)
{
	
}

void BouncyAI::OnCollide(Renderable& source, const Entity& target)
{
	// Compute direction of rectangular collision (spherical surely coming in v2.0 !)
	CollisionDir dir = CollissionSolver::Direction(source.GetBoundary(), target.GetBoundary());
	switch (dir) { // Abort if we're already heading the right direction
	case CollisionDir::Left:  if (source.Speed().x >= 0) return; source.Speed().x *= -1.0f; break;
	case CollisionDir::Right: if (source.Speed().x <= 0) return; source.Speed().x *= -1.0f; break;
	case CollisionDir::Top:   if (source.Speed().y >= 0) return; source.Speed().y *= -1.0f; break;
	case CollisionDir::Bottom:if (source.Speed().y <= 0) return; source.Speed().y *= -1.0f; break;
	}
}
