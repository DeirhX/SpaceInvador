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
	void Render() override { DrawSprite(*this); }
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

	// Various ways to get to IsDestroyed - value type vs. pointer type
	template <typename T, typename std::enable_if_t<!std::is_pointer<T>::value> * = 0>
	static bool IsDestroyed(T val) { return val.IsDestroyed(); }
	template <typename T, typename std::enable_if_t<std::is_pointer<T>::value> * = 0>
	static bool IsDestroyed(T val) { return val->IsDestroyed(); }
	
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
			while (++it != container.end() && IsDestroyed(*it)) { };
			return *this;
		}
	};

	Container vector;
public:
	auto Size() { return vector.size(); };
	TRenderable& operator[](int index) { return vector[index]; } // TODO: Make a custom iterator that skips dead items
	
	TRenderable& Add(TRenderable item)
	{
		auto& dead_item = std::find_if(vector.begin(), vector.end(), [this](auto val) { return IsDestroyed(val); });
		if (dead_item != vector.end()) {
			*dead_item = item;
			return *dead_item;
		}
		return vector.emplace_back(item);
	}
	void Remove(TRenderable& item) 
	{	// O(n) search is not really needed here. Just flag it destroyed and it will be recycled later, maybe.
		item.Destroy();
	}
	void Shrink()
	{	// Slice out dead objects on the beginning and end of deque. Don't invalidate references.
		while (!vector.empty() && Renderables::IsDestroyed(vector.front()))
			vector.pop_front();
		while (!vector.empty() && Renderables::IsDestroyed(vector.back()))
			vector.pop_back();
	}

	iterator begin()
	{	// Skip dead elements at the start
		auto it = iterator(vector, vector.begin());
		while (it != end() && IsDestroyed(*it))
			++it;
		return it;
	}
	iterator end() { return iterator(vector, vector.end()); }
};