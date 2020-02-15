#pragma once

class Score
{
	static constexpr char filename[] = "score.ftw";
	std::string filepath; // Forgive me for allowing a dynamic allocation here. const char [MAX_PATH] is so ugly.
public:
	float multiplier = 1.f;

	int current = 0;
	int max = 0;
public:
	Score();
	~Score() { Save(); }
	
	void Load();
	void Save();
	void Add(int points)
	{
		current += (int)std::round(points * multiplier);
		max = std::max(max, current);
	}
};
