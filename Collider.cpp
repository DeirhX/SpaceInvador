#include "pch.h"
#include "Collider.h"
#include "Renderables.h"


std::pair<int, int> CollissionSolver::GetSectorIndices(Position pos) const
{
	int x = std::clamp((int)((pos.x - bounds.min.x) / bounds.GetSize().x * divisions), 0, divisions - 1);
	int y = std::clamp((int)((pos.y - bounds.min.y) / bounds.GetSize().y * divisions), 0, divisions - 1);
	return { x, y };
}

CollissionSolver::Sector& CollissionSolver::GetSector(Position pos)
{
	auto i = GetSectorIndices(pos);
	return sectors[i.first + i.second * divisions];
}

std::basic_string<CollissionSolver::Sector*> CollissionSolver::GetSectors(Boundary bounds)
{
	auto result = std::basic_string<CollissionSolver::Sector*>();
	auto min = GetSectorIndices(bounds.min);
	auto max = GetSectorIndices(bounds.max);
	for(int i = min.first; i <= max.first; ++i)
		for (int j = min.second; j <= max.second; ++j)
		{
			result.push_back(&sectors[i + j * divisions]);
		}
	return result;
}

void CollissionSolver::Clear()
{
	for( auto& sector : sectors)
	{
		sector.objects.clear();
	}
}

void CollissionSolver::Populate(Entity& renderable)
{
	for (Sector* sector : GetSectors(renderable.GetBoundary()))
	{
		sector->objects.push_back(&renderable);
	}
}

void CollissionSolver::Solve()
{
	// Use to filter out same collisions happening in multiple sectors. Pointer equality should suffice.
	auto collisions = std::set<std::pair<Entity*, Entity*>>() ;
		
	for (auto& sector : sectors)
	{
		// O(n*n) for objects inside. High enough `divisions` should limit them to minimum.
		for(size_t i = 0; i < sector.objects.size(); ++i)
			for (size_t j = i + 1; j < sector.objects.size(); ++j)
			{
				if (sector.objects[i]->GetBoundary().Overlaps(sector.objects[j]->GetBoundary()))
				{
					/* Houston, we have a collision! */
					collisions.insert({ sector.objects[i], sector.objects[j] });
				}
			}
	}

	for (auto pair : collisions)
	{
		pair.first->Collide(*pair.second);
		pair.second->Collide(*pair.first);
	}
}

CollisionDir CollissionSolver::Direction(Boundary from, Boundary to)
{
	// Compute direction of rectangular collision (spherical surely coming in v2.0 !)

    // distance needed to touch
	float width = 0.5f * (from.GetSize().x + to.GetSize().x);
	float height = 0.5f * (from.GetSize().y + to.GetSize().y);
	// actual distance
	float dx = from.GetCentre().x - to.GetCentre().x;
	float dy = from.GetCentre().y - to.GetCentre().y;
	assert(abs(dx) <= width && abs(dy) <= height);

	// Touching axis will have width == dx or height == dy. Non-touching axis has width > dx or height > dy
	float wy = width * dy;
	float hx = height * dx;

	if (wy > hx) {
		return (wy > -hx) ? CollisionDir::Top : CollisionDir::Right;
	} else {
		return (wy > -hx) ? CollisionDir::Left : CollisionDir::Bottom;
	}

}