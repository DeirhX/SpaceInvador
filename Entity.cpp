#include "pch.h"
#include "World.h"
#include "Entity.h"

Entity::Entity(Position base, Size size)
: id(World::GetNextId()), location(base), size(size)
{
}

