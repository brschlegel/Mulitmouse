#pragma once
#include "Level.h"

class WackAMole :
	public Level
{
	public:
	WackAMole();
	vector<MouseGoal*> goals;
	void update();
	b2Vec2 startingPosition;
	MouseGoal* finish;
};