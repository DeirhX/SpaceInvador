#pragma once
#include "Vector.h"

class Scene
{
protected:
	float time = 0;
public:
	virtual void Advance(float elapsed) { time += elapsed; }
	virtual void Render() = 0;
protected:
	void RenderText(std::string_view text, Position centre, Size size);
};

class GameplayScene : public Scene
{
public:
	void Render() override;
};