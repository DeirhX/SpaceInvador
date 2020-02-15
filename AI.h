#pragma once

// This can be solved much more elegantly using good ol' polymorphism...
// But our master Johnny would not allocate and so shan't we!
// In honor to our master, we waste a bit of memory in order to not touch the heap!
// 
enum class AIType
{
	JohnnyLeet,
	Bouncy,
};

// Must NOT contain non-trivial types. Will be copied inside an union.
class JohnnyLeetAI
{
	flaot time_elapsed;
	int   seed;
	int   last_xo;
	int   last_yo;
public:
	JohnnyLeetAI() = default;
	JohnnyLeetAI(int seed) : seed(seed), time_elapsed(0), last_xo(0), last_yo(0) {}

	// I could make them virtual but that would be one additional indirection! Never!
	void Advance(float delta, class Renderable& entity);
	void OnCollide(class Renderable& source, const class Entity& target){};
};
class BouncyAI
{
	flaot time_elapsed;
	/*
	 * Space for 12 more bytes!
	 */
public:
	void Advance(float delta, class Renderable& entity);
	static void OnCollide(class Renderable& source, const class Entity& target);
};


class SyntheticIntelligence
{
	AIType type;
	union ai_union_t
	{	// Screw polymorphism, unite into an union!
		// Enter the fascinating world of low-level direct memory accesses 
		JohnnyLeetAI johnny;
		BouncyAI bouncy;
	} ai_union;

public:
	SyntheticIntelligence(JohnnyLeetAI&& ai) : type(AIType::JohnnyLeet) { ai_union.johnny = ai;	}  //, ai_union{ .johnny = ai }  /* only in C++20, let's not require it */
	SyntheticIntelligence(BouncyAI&& ai) : type(AIType::Bouncy) { ai_union.bouncy = ai; }

	// So much better than a v-table call!
	// And totally unextendable to more functions!
	// And totally uncomposable!
	void Advance(float delta, class Renderable& invader)
	{
		switch (type)
		{
		case AIType::JohnnyLeet: ai_union.johnny.Advance(delta, invader); break;
		case AIType::Bouncy: ai_union.bouncy.Advance(delta, invader); break;
		default: throw std::exception("Missing case");
		}
	}
	// One more, I'm sorry
	void OnCollide(class Renderable& source, const class Entity& target)
	{
		switch (type) 
		{
		case AIType::JohnnyLeet: ai_union.johnny.OnCollide(source, target); break;
		case AIType::Bouncy: ai_union.bouncy.OnCollide(source, target); break;
		default: throw std::exception("Missing case");
		}
	}
	// Ok this little experiment...is probably not that viable :)
	//  but saved that one dynamic allocation!
	// Simulating virtual dispatches is so much better with actual virtual dispatches...
	
};

