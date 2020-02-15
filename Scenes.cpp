#include "pch.h"
#include "Scenes.h"
#include "Sprites.h"
#include "Game.h"

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

void IntroScene::Render()
{
	RenderText("no mans sky", { -1, 30 }, Size{ 20.f});
	RenderText("multiplayer alpha", { -1, 100 }, Size{ 12.f});
	RenderText("best run", { -1, 290 }, Size{ 12.f}, 0xFFFF8866);
	RenderText("0 worlds", { -1, 350 }, Size{ 27.f});
	RenderText("space to start", { -1, 220}, Size{ 17.f}, 0xFF6688FF);
	RenderText("coming soon", { -1, 520 }, Size{ 10.f}, 0xFF66FF88);
	RenderText("aug 9 2016", { -1, 560}, Size{ 14.f}, 0xFF8866FF);
}

void GameplayScene::Render()
{
	static const char title[] = "score: ";
	std::string score_text = title + std::to_string(GetGame().Score());
	RenderText(score_text, { 200, 30 }, Size { 20.f, 20.f });
}

/*
 *  Your ship has been upgraded. It may feel the same but really its not.
 *  Your enemies have been upgraded. They may look the same but really theyre not.
 *  You have traveled to another world. It may look the same but its really not.
 * 
 */