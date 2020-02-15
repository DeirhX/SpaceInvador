#include "pch.h"
#include "Scenes.h"
#include "Sprites.h"
#include "Game.h"

void Scene::RenderText(std::string_view text, Position centre, Size size, DWORD mask)
{
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

void IntroScene::Render()
{
	RenderText("no mans sky", { 200, 30 }, Size{ 20.f, 20.f });
	RenderText("multiplayer alpha", { 190, 100 }, Size{ 12.f, 12.f });
	RenderText("best run", { 280, 210 }, Size{ 12.f, 12.f }, 0xFFFF8866);
	RenderText("0 worlds", { 180, 270 }, Size{ 25.f, 25.f });
	RenderText("coming soon", { 230, 520 }, Size{ 12.f, 12.f }, 0xFF66FF88);
	RenderText("aug 9 2016", { 210, 560}, Size{ 17.f, 17.f }, 0xFF8866FF);
}

void GameplayScene::Render()
{
	static const char title[] = "score: ";
	std::string score_text = title + std::to_string(GetGame().Score());
	RenderText(score_text, { 200, 30 }, Size { 20.f, 20.f });
}
