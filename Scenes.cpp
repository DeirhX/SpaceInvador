#include "pch.h"
#include "Scenes.h"
#include "Sprites.h"
#include "Game.h"

void Scene::RenderText(std::string_view text, Position centre, Size size)
{
	for (unsigned int n = 0; n < text.size(); ++n)
	{
		auto glyph = GetSprites().Glyphs[text[n]];
		if (glyph)	// Avoid unsupported characters
		{
			DrawSprite(glyph, (float)(n * 40 + centre.x), centre.y,
				size.x, size.y,
				(float)(sin(time * 0.1) * n * 0.01));
		}
	}
}

void IntroScene::Render()
{
	RenderText("no mans sky", { 200, 30 }, Size{ 20.f, 20.f });
	RenderText("multiplayer alpha", { 90, 130 }, Size{ 20.f, 20.f });
}

void GameplayScene::Render()
{
	static const char title[] = "score: ";
	std::string score_text = title + std::to_string(GetGame().Score());
	RenderText(score_text, { 200, 30 }, Size { 20.f, 20.f });
}
