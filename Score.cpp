#include "pch.h"
#include <Shlwapi.h>
#include <fstream>
#include "Score.h"

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
