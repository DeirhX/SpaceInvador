#include "pch.h"
#include "Sprites.h"

Sprites& GetSprites()
{
	static Sprites sprites; 
	return sprites;
}
