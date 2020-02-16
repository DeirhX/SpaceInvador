#include "pch.h"
#include "AI.h"
#include "Math.h"
#include "Invader.h"
#include "Collider.h"


void JohnnyLeetAI::Advance(float delta, Renderable& invader)
{
	// Master's work. This is great. And I mean it.
	// Do Not Touch. A sacred artifact.
	time_elapsed += delta;
	int xo = 0, yo = 0;
	int n1 = (int)time_elapsed + seed * seed + seed * seed * seed;              // space out circular animations of individual invaders to not happen at once (t + n^3 + n^2)
	int n2 = (int)time_elapsed + seed + seed * seed + seed * seed * seed * 3;  // same for downward jumps (t + 3n^3 + n^2 + n)
	if (((n1 >> 6) & 0x7) == 0x7)xo += (int)((1 - cos((n1 & 0x7f) / 64.0f  * math::two_pi)) * (20 +  ((seed * seed) % 9)));    // x part of circular motion, (cos of [2pi,4pi]), takes 64 time slices once in 512
	if (((n1 >> 6) & 0x7) == 0x7)yo += (int)((    sin((n1 & 0x7f) / 64.0f  * math::two_pi)) * (20 +  ((seed * seed) % 9)));	  // y part of circular motion (sin of [2pi,4pi]) takes 64 time slices once in 512
	if (((n2 >> 8) & 0xf) == 0xf)yo += (int)((1 - cos((n2 & 0xff) / 256.0f * math::two_pi)) * (150 + ((seed * seed) % 9)));   // additional downward jumps (cos of [0,2pi]), takes 256 time slices once in 4096

	// They say all things happen in cycles. Certainly they do for Johnny with clever use of cyclic trigonometric functions
	//  and bitmasks to limit their activation only to certain time slices. 
	
	invader.Location() +=  Vector2{ (float)(xo - last_xo), (float)(yo - last_yo) };

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
