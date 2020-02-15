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

	if (GetGame().GetScenes().active == GameSceneId::IntroGameplay)
	{
		Speed() = Position{ IsKeyDown('A') ? -7.0f : IsKeyDown('D') ? 7.0f : 0, 0 };
	}
	else
	{
		static constexpr float SpeedDecay = 0.98f;
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

	base::Advance(delta);

	GetWorld().bounds.MakeInside(Location());

	HandleShoot(delta);
}

void Player::Render()
{
	// The sprite is not really facing forward in our system, ugly hotfix
	if (GetGame().GetScenes().active != GameSceneId::IntroGameplay)
		Rotation() += math::half_pi;
	
	base::Render();
	crosshair.Render();

	if (GetGame().GetScenes().active != GameSceneId::IntroGameplay)
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
	}

}
