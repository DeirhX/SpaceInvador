#include "pch.h"

#include "Sprites.h"
#include "Game.h"


void StartGame()
{
	auto game = std::make_unique<Game>(); // We'll survive this dynamic allocation :)
	game->GameLoop();
}
