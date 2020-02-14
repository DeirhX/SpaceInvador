#pragma once
#include <vector>
#include "Vector.h"
#include "Entity.h"

class Renderable;

class Collider: public Entity 
{	using base = Entity;
public:
	Collider(Boundary boundary) : base{ boundary.GetCentre(), boundary.GetSize() } {}
	EntityType GetType() const override { return EntityType::WorldBoundary; }
};

// Collision solver that is not exactly quad-tree but much simpler
class CollissionSolver
{
	struct Sector
	{
		std::vector<Entity*> objects;
	};

	Boundary bounds;
	int divisions;
	std::vector<Sector> sectors;

protected:
	std::pair<int, int> GetSectorIndices(Position pos);
	Sector& GetSector(Position pos);
	std::basic_string<Sector*> GetSectors(Boundary bounds); // Utilize small string optimization to cheaply construct small 'vectors'
public:
	CollissionSolver(Boundary bounds, int divisions = 10) : bounds(bounds), divisions(divisions)
	{
		sectors.resize(divisions * divisions); // Assume roughly square area
	}

	void Clear();	// Prepare for new frame
	void Populate(Entity& renderable);
	void Solve();	// Notify all collision pairs
};

