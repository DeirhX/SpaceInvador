#pragma once
#include <vector>
#include "Vector.h"

class Renderable;

// Collision solver that is not exactly quad-tree but much simpler
class Collider
{
	struct Sector
	{
		std::vector<Renderable*> objects;
	};

	Boundary bounds;
	int divisions;
	std::vector<Sector> sectors;

protected:
	std::pair<int, int> GetSectorIndices(Position pos);
	Sector& GetSector(Position pos);
	std::basic_string<Sector*> GetSectors(Boundary bounds); // Utilize small string optimization to cheaply construct small 'vectors'
public:
	Collider(Boundary bounds, int divisions = 10) : bounds(bounds), divisions(divisions)
	{
		sectors.resize(divisions * divisions); // Assume roughly square area
	}

	void Clear();	// Prepare for new frame
	void Populate(Renderable& renderable);
	void Solve();	// Notify all collision pairs
};

