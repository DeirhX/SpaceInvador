#include "pch.h"
#include "World.h"
#include "Entity.h"

Entity::Entity()
: id(World::GetNextId())
{
}
