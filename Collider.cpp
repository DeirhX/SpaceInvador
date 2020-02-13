#include "pch.h"
#include "Collider.h"
#include "Renderables.h"

std::pair<int, int> Collider::GetSectorIndices(Position pos)
{
	int x = std::clamp((int)((pos.x - bounds.min.x) / divisions), 0, divisions - 1);
	int y = std::clamp((int)((pos.y - bounds.min.y) / divisions), 0, divisions - 1);
	return { x, y };
}

Collider::Sector& Collider::GetSector(Position pos)
{
	auto i = GetSectorIndices(pos);
	return sectors[i.first + i.second * divisions];
}

std::basic_string<Collider::Sector*> Collider::GetSectors(Boundary bounds)
{
	auto result = std::basic_string<Collider::Sector*>();
	auto min = GetSectorIndices(bounds.min);
	auto max = GetSectorIndices(bounds.max);
	for(int i = min.first; i <= max.first; ++i)
		for (int j = min.second; j <= max.second; ++j)
		{
			result.push_back(&sectors[i + j * divisions]);
		}
	return result;
}

void Collider::Clear()
{
	for( auto& sector : sectors)
	{
		sector.objects.clear();
	}
}

void Collider::Populate(Renderable& renderable)
{
	for (Sector* sector : GetSectors(renderable.GetBoundary()))
	{
		sector->objects.push_back(&renderable);
	}
}

void Collider::Solve()
{
	for (auto& sector : sectors)
	{
		// O(n*n) for objects inside. High enough `divisions` should limit them to minimum.
		for(int i = 0; i < sector.objects.size(); ++i)
			for (int j = i + 1; j < sector.objects.size(); ++j)
			{
				if (sector.objects[i]->GetBoundary().Overlaps(sector.objects[j]->GetBoundary()))
				{
					/* Houston, we have a collision! */
				}
			}
	}
}
