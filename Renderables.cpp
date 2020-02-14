#include "pch.h"
#include "Renderables.h"
#include "World.h"

void Renderable::Advance(float delta) 
{
	Location() += speed  * delta;
	//GetWorld().bounds.MakeInside(Location());

	base::Advance(delta);
}