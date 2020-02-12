#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Game.h"

void Player::Advance(float delta)
{
	static int count = 0;
	if (count) --count;
	if (!IsKeyDown(VK_SPACE)) count = 0;
	if (IsKeyDown(VK_SPACE) && count == 0)
	{
		auto& bullet = GetWorld().bullets.Add({ GetGame().sprites.Bullet, GetWorld().player.GetProjection(), {10} });
		bullet.Speed() = { 0, -2.5f };
		bullet.LifeDrain() = 0.5f;
		bullet.Rotation() = math::half_pi;
		count = 15;
	}
}
