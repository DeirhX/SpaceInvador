#pragma once
#include "Sprites.h"
#include "Vector.h"

class Entity
{
	bool is_destroyed = false; // Re-use dead objects so we don't need expensive allocations and vector shifts
	float life = 100.0f;
	float life_drain = 0;
public:
	virtual ~Entity() = default;
	void Destroy() { is_destroyed = true; }
	[[nodiscard]] bool IsAlive() const { return !is_destroyed; }
	[[nodiscard]] bool IsDead() const { return is_destroyed; }
	float& Life() { return life; }
	float& LifeDrain() { return life_drain; }
	
	virtual void Advance(float delta)
	{
		life -= life_drain * delta;
		if (life <= 0)
			Destroy();
	}
};

class Renderable : public Entity
{

protected:
	Sprite sprite;
	Position location;			// True origin in world
	Position transform = {};	// For temporary offsets
	Vector2 speed = {};			// For auto movement
	Size size = { 10.f, 10.f }; // Size of entity 
	float rotation = 0;			// Rotation of rendered sprite
	DWORD tint = 0xffffffff;	// Color mask

	// Cache for multiple accesses per frame (I know it's not worth it for this simple game ;)
	mutable bool pos_dirty = true;
	mutable Position projected_pos = {};

public:
	Renderable(Sprite sprite, Position base, Size size = { 10.f }) : sprite(sprite), location(base), size(size) {}
	Renderable& operator= (const Renderable& other) = default; // automatic
	// void SetTransform(Position newOffset) { transform = newOffset; pos_dirty = true; }
	void SetSize(float newSize) { size = { newSize, newSize }; }
	void SetSize(Size newSize) { size = newSize; }
	Position& Location() { pos_dirty = true; return location; };
	Position& Transform() { pos_dirty = true; return transform; }
	Vector2& Speed() { return speed; }
	float& Rotation() { return rotation; }
	DWORD& Tint() { return tint; }
	[[nodiscard]] Sprite GetSprite() const { return sprite; }
	[[nodiscard]] Size GetSize() const { return size; }
	[[nodiscard]] Vector2 GetSpeed() const { return speed; }
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
	[[nodiscard]] float GetRotation() const { return rotation; }
	[[nodiscard]] DWORD GetTint() const { return tint; }

	void Advance (float delta) override
	{
		Entity::Advance(delta);
		Location() += speed * delta;
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
	auto Size() { return vector.size(); };
	TRenderable& operator[](int index) { return vector[index]; } // TODO: Make a custom iterator that skips dead items
	TRenderable& Add(TRenderable&& item)
	{
		auto& dead_item = std::find_if(vector.begin(), vector.end(), [this](auto it) { return it.IsDead(); });
		if (dead_item != vector.end()) {
			*dead_item = TRenderable(item);
			return *dead_item;
		}
		return vector.emplace_back(std::forward<TRenderable&&>(item));
	}
	void Remove(TRenderable&& item) 
	{	// O(n) search is not really needed here. Just flag it destroyed and it will be recycled later, maybe.
		item.Destroy();
	}

	iterator begin()
	{	// Skip dead elements at the start
		auto it = iterator(vector, vector.begin());
		while (it != end() && (*it).IsDead())
			++it;
		return it;
	}
	iterator end() { return iterator(vector, vector.end()); }
};

using Bullet = Renderable;