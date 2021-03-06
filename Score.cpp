#include "pch.h"
#include <Shlwapi.h>
#include <fstream>
#include "Score.h"
#include "PhatLeetLib.h"
#include "World.h"

Score::Score()
{
	using namespace std::string_literals;
	// Ugly Win32 bits
	TCHAR szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	if (GetLastError())
		return;
	PathRemoveFileSpec(szFileName);
	this->filepath = szFileName + "\\"s + filename;
	Load();
}

void Score::Load()
{
	std::fstream file(filepath, std::ios::in);
	file >> max;
}

void Score::Save()
{
	std::fstream file(filepath, std::ios::out);
	file << max;
}

int Score::Add(int points)
{
	if (!GetWorld().player.IsAlive())
		return 0;
	int added = (int)std::round(points * multiplier);
	current += (int)std::round(points * multiplier);
	max = std::max(max, current);
	return added;
}

std::string Score::DiscoverWorld()
{
	std::string name;
	
	auto vowels = "aeiou"; // y sucks
	std::normal_distribution<float> dist(5, 3);
	int length = std::clamp( (int)std::round(dist(Random::generator)), 2, 10);
	for (int i=0; i < length; ++i)
	{
		if (i % 4 == 1)
			name += vowels[Random::Next(5)];
		else
			name += 'a' + Random::Next('z' - 'a');
	}
	return name;
}
