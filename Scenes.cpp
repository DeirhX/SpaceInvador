#include "pch.h"
#include "Scenes.h"
#include "Sprites.h"

void Scene::RenderText(std::string_view text, Position centre, Size size)
{
	for (unsigned int n = 0; n < text.size(); ++n)
	{
		auto glyph = GetSprites().Glyphs[text[n]];
		if (glyph)	// Avoid unsupported characters
		{
			DrawSprite(glyph, (float)(n * 40 + 150), 30,
				20, 20,
				(float)(sin(time * 0.1) * n * 0.01));
		}
	}
}

void GameplayScene::Render()
{
	static const char title[] = "score";
	RenderText(title, { 200, 30 }, Size { 20.f, 20.f });
}
