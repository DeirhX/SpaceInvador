#pragma once
#include "Sprites.h"

struct Position
{
	float x = 0;
	float y = 0;

	Position() = default;
	Position(float x, float y) : x(x), y(y) {}
	Position operator+ (const Position& other) const { return { x + other.x, y + other.y }; }
	Position operator- (const Position& other) const { return { x - other.x, y - other.y }; }
};

class Invader
{
public:
	const Sprite sprite;
	const Position base_pos;
private:
	float size = 10;
	Position offset_pos = {};
	
	// Cache for multiple accesses per frame (I know it's not worth it for this simple game ;)
	mutable bool pos_dirty = true;
	mutable Position projected_pos = {};

public:
	Invader(Sprite sprite, Position base, float size = 10) : sprite(sprite), base_pos(base), size(size) {}
	void SetOffset(Position newOffset) { offset_pos = newOffset; pos_dirty = true; }
	void SetSize(float newSize) { size = newSize; }
	[[nodiscard]] float GetSize() const { return size; }
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
	std::vector<Invader> invaders;
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

