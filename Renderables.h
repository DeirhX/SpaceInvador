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

	// Cache for multiple accesses per frame (I know it's not worth it for this simple game ;)
	mutable bool pos_dirty = true;
	mutable Position projected_pos = {};

public:
	Renderable(Sprite sprite, Position base, Size size = { 10.f }) : sprite(sprite), location(base), size(size) {}
	void SetTransform(Position newOffset) { transform = newOffset; pos_dirty = true; }
	void SetSize(float newSize) { size = { newSize, newSize }; }
	void SetSize(Size newSize) { size = newSize; }
	Position& Location() { pos_dirty = true; return location; };
	Position& Transform() { pos_dirty = true; return transform; }
	[[nodiscard]] Size GetSize() const { return size; }
	[[nodiscard]] Position GetTransform() const { return transform; };
	[[nodiscard]] Position GetLocation() const { return location; };
	[[nodiscard]] Position GetProjection() const
	{
		// Compute only if changed
		if (pos_dirty)
			projected_pos = location + transform; // Very much like WVP matrix multiplication!  We saved a lot of instructions here!

		pos_dirty = false;
		return projected_pos;
	}
};

using Invader = Renderable;
using Player = Renderable;
