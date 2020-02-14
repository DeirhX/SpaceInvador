#pragma once
#include "Sprites.h"
#include "Vector.h"
#include "Entity.h"
#include "PhatLeetLib.h"

class Renderable : public Entity
{	using base = Entity;

protected:
	Sprite sprite;
	Vector2 speed = {};			// For auto movement
	float rotation = 0;			// Rotation of rendered sprite
	DWORD tint = 0xffffffff;	// Color mask

public:
	Renderable(Sprite sprite, Position base, Size size) : base(base, size), sprite(sprite) {}
	Renderable& operator= (const Renderable& other) = default; // automatic

	// Setters
	Vector2& Speed() { return speed; }
	float& Rotation() { return rotation; }
	DWORD& Tint() { return tint; }

	// Getters
	[[nodiscard]] Sprite GetSprite() const { return sprite; }
	[[nodiscard]] Vector2 GetSpeed() const { return speed; }
	[[nodiscard]] float GetRotation() const { return rotation; }
	[[nodiscard]] DWORD GetTint() const { return tint; }

	void Advance(float delta) override;
	virtual void Render() { DrawSprite(*this); }
};

class Decoration : public Renderable
{	
	using base = Renderable;
protected:
	float fade_begin = 0; // Life at which to being linearly fading out
public:
	float& FadeBegin() { return fade_begin; }

	Decoration(const Sprite& sprite, const Position& base, const Size& size, const Vector2& speed = { 0, 0 })
		: Renderable(sprite, base, size)
	{
		Speed() = speed;
	}
	Decoration(const Sprite& sprite, const Position& base, const Size& size, const Vector2& speed, float life)
		: Decoration(sprite, base, size, speed)
	{
		Life() = life;
		LifeDrain() = 1.f;
		FadeBegin() = life;
	}
	[[nodiscard]] virtual EntityType GetType() const { return EntityType::Decoration; }
	void Advance(float delta) override 
	{
		base::Advance(delta);

		if (Life() < FadeBegin()) {
			tint = ((uint8_t)(255 * Life() / FadeBegin())  << 24) | (0x00ffffff & Tint());
		}
	}
};


// Effective container for storing an array of renderables - deleting does not shift, dead objects can be reused later
//  and references to live objects are valid forever.
// We risk fragmentation after long use but let's have this as an experiment how to reduce the number of dynamic allocations
//  to minimum.
// Iterator and foreach support - skips over dead elements 
template <typename TRenderable>
class Renderables
{
	using Container = std::deque<TRenderable>;  // As long we grow/shrink on start/end, element references are valid forever
	class iterator
	{
		Container& container; 
		typename Container::iterator it;
	public:
		iterator(Container& container, typename Container::iterator it): container(container), it(it) {}
		TRenderable& operator*() const { return *it; }
		bool operator!= (iterator other) { return it != other.it; }
		iterator operator++() // prefix increment
		{	// Advance over dead elements
			while (++it != container.end() && (*it).IsDestroyed()) { };
			return *this;
		}
	};

	Container vector;
public:
	auto Size() { return vector.size(); };
	TRenderable& operator[](int index) { return vector[index]; } // TODO: Make a custom iterator that skips dead items
	TRenderable& Add(TRenderable&& item)
	{
		auto& dead_item = std::find_if(vector.begin(), vector.end(), [this](auto it) { return it.IsDestroyed(); });
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
	void Shrink()
	{	// Slice out dead objects on the beginning and end of deque. Don't invalidate references.
		while (!vector.empty() && *vector.front().IsDestroyed())
			vector.pop_front();
		while (!vector.empty() && *vector.back().IsDestroyed())
			vector.pop_back();
	}

	iterator begin()
	{	// Skip dead elements at the start
		auto it = iterator(vector, vector.begin());
		while (it != end() && (*it).IsDestroyed())
			++it;
		return it;
	}
	iterator end() { return iterator(vector, vector.end()); }
};