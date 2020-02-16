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

void GameOverScene::Advance(float elapsed)
{
	GetWorld().Advance(elapsed);
	GetWorld().Render();
}

void GameOverScene::Render()
{
	float y = 240;
	RenderText("game over", { -1, y }, Size{ 30.f - 2.f * std::min(time, 5.0f) });
	y += 200;
	RenderText("to continue send 1btc", { -1, y }, Size{ 12.f });
	RenderText("and purchase more crystals", { -1, y += 40.f}, Size{ 10.f });
}

void IntroScene::Begin(World& world)
{
	world = World{Player{}};
	time = 0;
	GetGame().Score().Reset();
}

void IntroScene::Render()
{
	float y = 90;
	char score_text[18]; // Old skool!
	sprintf_s(score_text, "%d worlds", GetGame().Score().max);
	
	RenderText("no mans sky", { -1, y }, Size{ 20.f});
	RenderText("multiplayer alpha", { -1, y += 70}, Size{ 12.f});
	y += 100;
	RenderText("best run", { -1, y}, Size{ 12.f}, 0xFFFFFFFF);
	RenderText(score_text, { -1, y += 65 }, Size{ 25.f});
	y += 100;
	RenderText("space to start", { -1, y}, Size{ 17.f}, 0xFFFFFFFF);
	RenderText("coming soon", { -1, y += 100 }, Size{ 10.f}, 0xFFFFFFFF);
	RenderText("aug 9 2016", { -1, y += 40}, Size{ 14.f}, 0xFFFFFFFF);
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
							 (int)world.invaders.Size(), JohnnyLeetAI{n + 1} });
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


/*
 * First Victory Scene 
 */


void FirstVictoryScene::Render()
{
	float y = 90;
	RenderText("congratulations", { -1, y }, Size{ 20.f });
	RenderText("it is time to leave", { -1, y += 50}, Size{ 12.f });
	RenderText("the planet", { -1, y += 50 }, Size{ 15.f }, 0xFFFFFFFF);
	y += 140;
	RenderText("thrusters engaged", { -1, y += 0 }, Size{ 22.f }, 0xFFFFFFFF);
	RenderText("use w to thrust", { -1, y += 70 }, Size{ 17.f }, 0xFFFFFFFF);
	RenderText("use s to brake", { -1, y += 50 }, Size{ 17.f }, 0xFFFFFFFF);
	RenderText("space to start", { -1, y += 50 }, Size{ 17.f }, 0xFFFFFFFF);
}

void SecondVictoryScene::Render()
{
	float y = 90;
	RenderText("approaching worm hole", { -1, y }, Size{ 17.f });
	RenderText("", { -1, y += 50 }, Size{ 12.f });
	RenderText("enter to warp", { -1, y += 50 }, Size{ 15.f }, 0xFFFFFFFF);
	y += 140;
	RenderText("your enemies have been upgraded", { -1, y += 0 }, Size{ 10.f }, 0xFFFFFFFF);
	RenderText("they may look the same", { -1, y += 50 }, Size{ 11.f }, 0xFFFFFFFF);
	RenderText("but really theyre not", { -1, y += 40 }, Size{ 11.f }, 0xFFFFFFFF);
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
	wormhole.Location() = world.bounds.GetCentre();
	world.scene_extras.Add(&wormhole);
	
	for (int n = 0; n < 40; ++n)
	{
		Position position;
		if (n % 5 != 0)
		{
			// Generate well outside visible screen
			std::uniform_real_distribution<float> dist_pos(-500, 500);
			position = Position{ dist_pos(Random::generator), dist_pos(Random::generator) };
			position += GetWorld().bounds.GetCentre();
			position.x += GetWorld().bounds.GetSize().x * ((position.x > GetWorld().bounds.GetCentre().x) ? 1 : -1);
			position.y += GetWorld().bounds.GetSize().y * ((position.y > GetWorld().bounds.GetCentre().y) ? 1 : -1);
		}
		else
		{	// Generate at wormhole
			std::uniform_real_distribution<float> dist_pos(-40, 40);
			position = Position{ dist_pos(Random::generator) + wormhole.GetLocation().x, dist_pos(Random::generator) + wormhole.GetLocation().y };
		}
		
		auto invader = Invader{ GetSprites().Enemy,
							   position,
							   (int)world.invaders.Size(), BouncyAI{} };

		std::uniform_real_distribution<float> dist_spd(-3.0f, 3.0f);
		invader.Speed() = { dist_spd(Random::generator), dist_spd(Random::generator) };
		world.invaders.Add(invader);
	}
}


/*  Useful messages:
 *
 *  Your ship has been upgraded. It may feel the same but really its not.
 *  Your enemies have been upgraded. They may look the same but really theyre not.
 *  You have traveled to another world. It may look the same but its really not.
 * 
 */
