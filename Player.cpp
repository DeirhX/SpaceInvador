#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Game.h"
#include <algorithm>
#include "Math.h"

void Player::Advance(float delta)
{
	auto movement_offset = Position{ IsKeyDown('A') ? -7.0f : IsKeyDown('D') ? 7.0f : 0, 0 };
	Location() += movement_offset;

	float mx, my;
	GetMousePos(mx, my);
	crosshair.Location() = { mx, my };
	HandleShoot(delta);

	Renderable::Advance(delta);
}

void Player::Render()
{
	Renderable::Render();
	crosshair.Render();
}

void Player::HandleShoot(float delta)
{

	shoot_energy = std::clamp(shoot_energy + delta, 0.f, ShootEnergyMax);

	if (!IsKeyDown(VK_LBUTTON) || shoot_energy == ShootEnergyMax)
		reloaded = true;
	if (IsKeyDown(VK_LBUTTON) && reloaded && shoot_energy >= ShotCost)
	{
		shoot_energy -= ShotCost;
		reloaded = false;

		Vector2 dir = { crosshair.GetProjection() - GetProjection() };
		dir.Normalize();

		auto& bullet = GetWorld().bullets.Add({ GetGame().sprites.Bullet, GetWorld().player.GetProjection(), {10} });
		bullet.Speed() = 2.5f * dir;
		bullet.LifeDrain() = 0.5f;
		bullet.Rotation() = math::ToRadians(dir);
	}

}
