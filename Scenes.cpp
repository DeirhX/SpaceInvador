#include "pch.h"
#include "Scenes.h"
#include "Sprites.h"
#include "Game.h"
#include "Decorations.h"

void Scene::RenderText(std::string_view text, Position centre, Size size, DWORD mask)
{
	if (centre.x == -1.0f)
	{
		auto h_centre = GetWorld().bounds.GetCentre();
		centre.x = h_centre.x - text.size() * size.x;
	}
	
	for (unsigned int n = 0; n < text.size(); ++n)
	{
		auto glyph = GetSprites().Glyphs[text[n]];
		if (glyph)	// Avoid unsupported characters
		{
			DrawSprite(glyph, (float)(n * 2.0f* size.x + centre.x), centre.y,
				size.x, size.y,
				(float)(sin(time * 0.1) * n * 0.01),
				mask);
		}
	}
}

void GameOverScene::Begin(World& world)
{
	time = 0;
	score_text = "score " + std::to_string(GetGame().GetScore());
}

void GameOverScene::Advance(float elapsed)
{
	GetWorld().Advance(elapsed);
	GetWorld().Render();
}

void GameOverScene::Render()
{
	float y = 120;
	RenderText(score_text, { -1, y }, Size{ 20.f });
	y += 160;
	RenderText("game over", { -1, y }, Size{ 30.f - 2.f * std::min(time, 5.0f) });
	y += 220;
	RenderText("to continue send 1btc", { -1, y }, Size{ 12.f });
	RenderText("and purchase more dlcs", { -1, y += 40.f}, Size{ 10.f });
}

void IntroScene::Begin(World& world)
{
	world = World{Player{}};
	pressed = true;
	time = 0;
	GetGame().Score().Reset();
}

void IntroScene::Render()
{
	GetGame().Score().Reset();
	char score_text[18]; // Old skool!
	sprintf_s(score_text, "%d worlds", GetGame().Score().max);

	float y = 40;
	RenderText("no mans sky", { -1, y }, Size{ 20.f});
	RenderText("multiplayer alpha", { -1, y += 50}, Size{ 12.f});
	y += 130;
	RenderText("best run", { -1, y}, Size{ 12.f}, 0xFFFFFFFF);
	RenderText(score_text, { -1, y += 65 }, Size{ 25.f});
	y += 140;
	RenderText("space to start", { -1, y}, Size{ 17.f}, 0xFFFFFFFF);
	RenderText("you may not meet other players", { -1, y += 100 }, Size{ 9.f}, 0xFFFFFFFF);
	RenderText("because they are very far away", { -1, y += 40}, Size{ 9.f}, 0xFFFFFFFF);
}

void ControlsScene::Begin(World& world)
{
	time = 0;
	GetGame().Score().world = GetGame().Score().DiscoverWorld();
	discover_text = "planet " + GetGame().Score().world;
}

void ControlsScene::Render()
{
	float y = 100;
	RenderText("approaching", { -1, y }, Size{ 18.f });
	RenderText(discover_text, { -1, y+=60 }, Size{ 20.f });
	y += 200;
	RenderText("use a to move left", { -1, y += 0 }, Size{ 17.f }, 0xFFFFFFFF);
	RenderText("use d to move right", { -1, y += 50 }, Size{ 17.f }, 0xFFFFFFFF);
	RenderText("mouse to shoot", { -1, y += 50 }, Size{ 17.f }, 0xFFFFFFFF);
}


/*
 * First Gameplay Scene
 */
void GameplayScene::Begin(World& world)
{
	world = World { Player { GetSprites().Player, {400.f, 550.f}, {50.f} } };
	for (int n = 0; n < 50; ++n)
	{
		world.invaders.Add({ GetSprites().Enemy,
							 Position{ (n % 10) * 60.f + 120,(n / 10) * 60.f + 70 },
							 (int)world.invaders.Size(), JimmyLeetAI{n + 1} });
	}
}

void GameplayScene::Advance(float elapsed)
{
	Scene::Advance(elapsed);
	GetWorld().Advance(elapsed);
	GetWorld().Render();
}

void GameplayScene::Render()
{
	static const char title[] = "score: ";
	std::string score_text = title + std::to_string(GetGame().GetScore());
	RenderText(score_text, { 200, 30 }, Size { 20.f, 20.f });
}

void GameplayScene::GenerateEnemiesOutsideScreen(World& world, int count, float speed_mult)
{
	for (int i = 0; i < count; ++i)
	{
		// Generate well outside visible screen
		std::uniform_real_distribution<float> dist_pos(-500, 500);
		Position position = Position{ dist_pos(Random::generator), dist_pos(Random::generator) };
		position += GetWorld().bounds.GetCentre();
		position.x += GetWorld().bounds.GetSize().x * ((position.x > GetWorld().bounds.GetCentre().x) ? 1 : -1);
		position.y += GetWorld().bounds.GetSize().y * ((position.y > GetWorld().bounds.GetCentre().y) ? 1 : -1);

		// Head roughly towards centre
		std::uniform_real_distribution<float> rnd_float(-1.0f, 1.0f);
		Vector2 speed = (2.0f + rnd_float(Random::generator)) * (world.GetBoundary().GetCentre() - position).Normalize() * speed_mult;
		speed.x += 0.15f * rnd_float(Random::generator);;
		speed.y += 0.15f * rnd_float(Random::generator);

		auto invader = Invader{ GetSprites().Enemy,
						   position,
						   (int)world.invaders.Size(), BouncyAI{} };
		invader.Speed() = speed;
		world.invaders.Add(invader);
	}
}

void GameplayScene::GenerateEnemiesAroundPoint(World& world, Boundary bounds, int count)
{
	for (int i = 0; i < count; ++i)
	{
		// Generate uniformly inside boundary
		std::uniform_real_distribution<float> dist_pos(-40, 40);
		Position position = { dist_pos(Random::generator) + bounds.GetCentre().x, dist_pos(Random::generator) + bounds.GetCentre().y };

		// Randomize direction and speed
		std::uniform_real_distribution<float> dist_spd(-3.0f, 3.0f);
		Vector2 speed = { dist_spd(Random::generator), dist_spd(Random::generator) };

		auto invader = Invader{ GetSprites().Enemy,
							   position,
							   (int)world.invaders.Size(), BouncyAI{} };
		invader.Speed() = speed;
		world.invaders.Add(invader);
	}
}


/*
 * First Victory Scene 
 */


void FirstVictoryScene::Begin(World& world)
{
	TextScene::Begin(world);
	GetGame().Score().multiplier += 1;
}

void FirstVictoryScene::Render()
{
	float y = 90;
	RenderText("congratulations", { -1, y }, Size{ 20.f });
	RenderText("it is time to leave", { -1, y += 50}, Size{ 12.f });
	RenderText("the planet", { -1, y += 50 }, Size{ 15.f }, 0xFFFFFFFF);
	y += 140;
	RenderText("thrusters engaged", { -1, y += 0 }, Size{ 20.f }, 0xFFFFFFFF);
	RenderText("use w to thrust", { -1, y += 70 }, Size{ 17.f }, 0xFFFFFFFF);
	RenderText("use s to brake", { -1, y += 50 }, Size{ 17.f }, 0xFFFFFFFF);
	RenderText("space to start", { -1, y += 50 }, Size{ 17.f }, 0xFFFFFFFF);
}

void ThrustVictoryScene::Begin(World& world)
{
	TextScene::Begin(world);
	GetGame().Score().multiplier += 1;
}

void ThrustVictoryScene::Render()
{
	float y = 90;
	RenderText("approaching worm hole", { -1, y }, Size{ 17.f });
	RenderText("", { -1, y += 50 }, Size{ 12.f });
	RenderText("enter to warp", { -1, y += 50 }, Size{ 15.f }, 0xFFFFFFFF);
	y += 280;
	RenderText("thrusters have been upgraded", { -1, y += 0 }, Size{ 10.f }, 0xFFFFFFFF);
	RenderText("they may look the same", { -1, y += 40 }, Size{ 11.f }, 0xFFFFFFFF);
	RenderText("but really theyre not", { -1, y += 40 }, Size{ 11.f }, 0xFFFFFFFF);
}

void WormholeVictoryScene::Begin(World& world)
{
	GetGame().Score().multiplier += 1;
	time = 0;
	GetGame().Score().world = GetGame().Score().DiscoverWorld();
	discover_text = GetGame().Score().world + " dlc";
}

void WormholeVictoryScene::Render()
{
	float y = 90;
	RenderText("the warp failed", { -1, y }, Size{ 17.f });
	RenderText("you didnt buy the", { -1, y += 60 }, Size{ 11.f });
	RenderText(discover_text, { -1, y += 40 }, Size{ 12.f });
	y += 190;
	RenderText("you are now in the middle", { -1, y += 0 }, Size{ 10.f }, 0xFFFFFFFF);
	RenderText("of nowhere", { -1, y += 35 }, Size{ 12.f }, 0xFFFFFFFF);
	RenderText("good luck", { -1, y += 80 }, Size{ 18.f }, 0xFFFFFFFF);
}

void AmbushVictoryScene::Begin(World& world)
{
	GetGame().Score().multiplier += 1;
	world = World{ Player{} };
	wave_num += 1;
	next_wave_text = std::to_string(GetInvaderCount()) + " more invaders";
}

void AmbushVictoryScene::Render()
{
	float y = 90;
	RenderText("there is no end in sight", { -1, y }, Size{ 16.f });
	RenderText("unless you buy", { -1, y += 50 }, Size{ 11.f });
	RenderText("the end dlc", { -1, y += 40 }, Size{ 12.f });
	y += 140;
	RenderText(next_wave_text, { -1, y += 0 }, Size{ 15.f }, 0xFFFFFFFF);
	RenderText("approaching", { -1, y += 50 }, Size{ 18.f }, 0xFFFFFFFF);
	RenderText("good luck", { -1, y += 100 }, Size{ 20.f }, 0xFFFFFFFF);
}


void ThrustGameplayScene::Begin(World& world)
{
	world = World{ Player { GetSprites().Player, {400.f, 500.f}, {50.f} } };
	for (int n = 0; n < 20; ++n)
	{
		auto invader = Invader{ GetSprites().Enemy,
							   Position{ (n % 10) * 60.f + 120,(n / 10) * 60.f + 70 },
							   (int)world.invaders.Size(), BouncyAI{} };
		std::uniform_real_distribution<float> dist(-3.0f, 3.0f);
		invader.Speed() = { dist(Random::generator), dist(Random::generator) };
		world.invaders.Add(invader);
	}
}

void WormholeGameplayScene::Begin(World& world)
{
	world = World{ Player { GetSprites().Player, {400.f, 500.f}, {50.f} } };
	wormhole = Wormhole{ world.bounds.GetCentre(), {50, 40} };
	world.scene_extras.Add(&wormhole);

	GameplayScene::GenerateEnemiesAroundPoint(world, Boundary{ wormhole.GetLocation(), 80.f }, 8);
	GameplayScene::GenerateEnemiesOutsideScreen(world, 30);
}

void AmbushGameplayScene::Begin(World& world)
{
	world = World{ Player { GetSprites().Player, {400.f, 500.f}, {50.f} } };

	const auto& scene_data = GetGame().GetScenes().ambush_victory;
	GameplayScene::GenerateEnemiesOutsideScreen(world, scene_data.GetInvaderCount(), 1.f + 0.1f * scene_data.wave_num );
}



/*  Useful messages:
 *
 *  Your ship has been upgraded. It may feel the same but really its not.
 *  Your enemies have been upgraded. They may look the same but really theyre not.
 *  You have traveled to another world. It may look the same but its really not.
 * 
 */
