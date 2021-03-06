#include "pch.h"
#include "Player.h"
#include "World.h"
#include "Game.h"
#include "Math.h"
#include "Sounds.h"

void Player::Advance(float delta)
{
	float mx, my;
	GetMousePos(mx, my);
	crosshair.Location() = { mx, my };

	if (IsActive() && IsAlive())
	{
		HandleShoot(delta);
		HandleMovement(delta);
	}
	else
	{
		Speed() *= 0.97f;
	}

	base::Advance(delta);

	thrust_fx_timer += delta;
	if (thrust_fx_timer > thrust_fx_tick && (GetGame().GetScenes().active != GameSceneId::InvadersGameplay))
	{
		thrust_fx_timer = 0;
		if (GetSpeed().GetLength() >= 2.0f)
		{
			float variation = Random::Next(-math::half_pi * 0.15f, math::half_pi * 0.15f);
			Vector2 offset = -5.f * math::FromRadians(GetRotation());
			SoundEffect::Play("ss", GetLocation() + offset, -0.2f * math::FromRadians(GetRotation() + variation));
		}
		
	}

	GetWorld().bounds.MakeInside(Location());
}

void Player::Render()
{
	// The sprite is not really facing forward in our system, ugly hotfix
	if (GetGame().GetScenes().active != GameSceneId::InvadersGameplay)
		Rotation() += math::half_pi;
	
	base::Render();
	crosshair.Render();

	if (GetGame().GetScenes().active != GameSceneId::InvadersGameplay)
		Rotation() -= math::half_pi;
}

void Player::Collide(const Entity& other)
{
	if (other.GetType() == EntityType::WorldBoundary)
	{
		BouncyAI::OnCollide(*this, other);
		Speed() *= 0.7f;
	}
	else if (other.GetType() == EntityType::Invader)
	{
		Life() = 0;
		SoundEffect::Play("crash", GetLocation(), { 0, -1 });
		SoundEffect::Play("boom", GetLocation(), { 0, +1 });
		SoundEffect::Play("clang", GetLocation() + Vector2{ 0, 10.f }, { 0, -1 });
	}
}

void Player::HandleMovement(float delta)
{
	static constexpr float SpeedDecay = 0.98f;
	if (GetGame().GetScenes().active == GameSceneId::InvadersGameplay)
	{
		Speed() = Position{ IsKeyDown('A') ? -7.0f : IsKeyDown('D') ? 7.0f : 0, 0 };
	}
	else
	{
		auto prev_speed = GetSpeed();

		bool relative_scheme = true;
		if (relative_scheme)
		{
			if (IsKeyDown('W'))
				Speed() += 0.1f * math::FromRadians(Rotation());
			if (IsKeyDown('S'))
				Speed() += 0.1f * math::FromRadians(Rotation() + math::pi);
			if (IsKeyDown('A'))
				Speed() += 0.1f * math::FromRadians(thrust_orientation - math::half_pi);
			if (IsKeyDown('D'))
				Speed() += 0.1f * math::FromRadians(thrust_orientation + math::half_pi);

			Rotation() = math::ToRadians(crosshair.GetLocation() - GetLocation());
		}
		else
		{
			if (IsKeyDown('W'))
				Speed() += 0.1f * math::FromRadians(Rotation());
			if (IsKeyDown('S'))
				Speed() += 0.1f * math::FromRadians(Rotation() + math::pi);
			if (IsKeyDown('A'))
				Rotation() -= delta * 0.03f * math::pi;
			if (IsKeyDown('D'))
				Rotation() += delta * 0.03f * math::pi;
		}

		if (prev_speed != GetSpeed())
			thrust_orientation = Rotation();
		else
			Speed() *= SpeedDecay;
	}
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
		float forward_force = std::max(0.f, Speed() * dir); // Get scalar of thrusting momentum aligned to bullet direction

		auto& bullet = GetWorld().bullets.Add({ GetGame().sprites.Bullet, GetWorld().player.GetProjection() + Size{0, -15.f}, {10} });
		bullet.Speed() = (forward_force + 4.5f) * dir;
		bullet.LifeDrain() = 0.5f;
		bullet.Rotation() = math::ToRadians(dir);

		SoundEffect::Play("bam", GetLocation(), { 0, -1 });
	}

}
