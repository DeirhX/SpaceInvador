#pragma once
#include "Sprites.h"
#include "Vector.h"

class Renderable
{
public:
	const Sprite sprite;
private:
	Position location;        // True origin in world
	Position transform = {}; // For temporary offsets
	Size size = { 10.f, 10.f };
	float rotation = 0;
	bool is_destroyed = false; // Re-use dead objects so we don't need expensive allocations and vector shifts

	// Cache for multiple accesses per frame (I know it's not worth it for this simple game ;)
	mutable bool pos_dirty = true;
	mutable Position projected_pos = {};

public:
	Renderable(Sprite sprite, Position base, Size size = { 10.f }) : sprite(sprite), location(base), size(size) {}
	void SetTransform(Position newOffset) { transform = newOffset; pos_dirty = true; }
	void SetSize(float newSize) { size = { newSize, newSize }; }
	void SetSize(Size newSize) { size = newSize; }
	void Destroy() { is_destroyed = true; }
	Position& Location() { pos_dirty = true; return location; };
	Position& Transform() { pos_dirty = true; return transform; }
	[[nodiscard]] bool IsAlive() const { return !is_destroyed; }
	[[nodiscard]] bool IsDead() const { return is_destroyed; }
	[[nodiscard]] Size GetSize() const { return size; }
	[[nodiscard]] Position GetTransform() const { return transform; };
	[[nodiscard]] Position GetLocation() const { return location; };
	[[nodiscard]] Position GetProjection() const
	{
		// Compute only if changed
		if (pos_dirty)
			projected_pos = location + transform; // Very much like WVP matrix multiplication!  We saved a lot of instructions here by caching it!

		pos_dirty = false;
		return projected_pos;
	}
};

// Effective container for storing an array of renderables - deleting does not shift, dead objects can be reused later.
// Iterator and foreach support - skips over dead elements 
template <typename TRenderable>
class Renderables
{
	class iterator
	{
		std::vector<TRenderable>& container;
		typename std::vector<TRenderable>::iterator it;
	public:
		iterator(std::vector<TRenderable> & container, typename std::vector<TRenderable>::iterator it): container(container), it(it) {}
		TRenderable& operator*() const { return *it; }
		bool operator!= (iterator other) { return it != other.it; }
		iterator operator++() // prefix increment
		{	// Advance over dead elements
			while (++it != container.end() && (*it).IsDead()) { };
			return *this;
		}
	};

	std::vector<TRenderable> vector;
public:
	TRenderable& operator[](int index) { return vector[index]; } // TODO: Make a custom iterator that skips dead items
	TRenderable& Add(TRenderable&& item) { return vector.emplace_back(std::forward<TRenderable&&>(item)); }
	TRenderable& Remove(TRenderable&& item) 
	{	// O(n) search is not really needed here. Just flag it destroyed and it will be recycled later, maybe.
		item.Destroy();
	}

	iterator begin() { return iterator(vector, vector.begin()); }
	iterator end() { return iterator(vector, vector.end()); }
};

using Invader = Renderable;
using Player = Renderable;
using Bullet = Renderable;