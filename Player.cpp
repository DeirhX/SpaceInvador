#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Game.h"
#include <algorithm>

void Player::Advance(float delta)
{
	auto movement_offset = Position{ IsKeyDown(VK_LEFT) ? -7.0f : IsKeyDown(VK_RIGHT) ? 7.0f : 0, 0 };
	Location() += movement_offset;
	
	shoot_energy = std::clamp(shoot_energy + delta, 0.f, ShootEnergyMax);

	if (!IsKeyDown(VK_SPACE) || shoot_energy == ShootEnergyMax)
		reloaded = true;
	if (IsKeyDown(VK_SPACE) && reloaded && shoot_energy >= ShotCost)
	{
		shoot_energy -= ShotCost;
		reloaded = false;
		
		auto& bullet = GetWorld().bullets.Add({ GetGame().sprites.Bullet, GetWorld().player.GetProjection(), {10} });
		bullet.Speed() = { 0, -2.5f };
		bullet.LifeDrain() = 0.5f;
		bullet.Rotation() = math::half_pi;
	}

	Renderable::Advance(delta);
}
