#pragma once
#include "Sprites.h"
#include "vector.h"

class Renderable
{
public:
	const Sprite sprite;
	const Position base_pos;
private:
	Size size = { 10.f, 10.f };
	Position offset_pos = {};
	
	// Cache for multiple accesses per frame (I know it's not worth it for this simple game ;)
	mutable bool pos_dirty = true;
	mutable Position projected_pos = {};

public:
	Renderable(Sprite sprite, Position base, Size size = { 10.f }) : sprite(sprite), base_pos(base), size(size) {}
	void SetOffset(Position newOffset) { offset_pos = newOffset; pos_dirty = true; }
	void SetSize(float newSize) { size = { newSize, newSize }; }
	void SetSize(Size newSize) { size = newSize; }
	[[nodiscard]] Size GetSize() const { return size; }
	[[nodiscard]] Position GetOffset() const { return offset_pos; };
	[[nodiscard]] Position GetPosition() const
	{
		// Compute only if changed
		if (pos_dirty)
			projected_pos = base_pos + offset_pos;

		pos_dirty = false;
		return projected_pos;
	} 
};

class Game
{
	using Invader = Renderable;
	std::vector<Renderable> invaders;
	int time = 0;

	struct bullet
	{
		float BX = 0;
		float BY = 0;
		float BA = 0;
	};
	bullet bullets[10];
	float UX = 400, UY = 550;
	Sprites sprites;

public:
	Game();
	void RenderTitle(int time);
	void RenderBullets();
	void ProcessFire();
	void MoveAndRenderEnemies(int time);
	void GameLoop();
};

