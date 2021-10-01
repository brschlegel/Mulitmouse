#pragma once
#include "Level.h"

class ClickRace :
	public Level
{
	public:
		ClickRace();
		vector<MouseGoal*> goals;
		void update();
		b2Vec2 startingPosition;
		Goal* goal;
		Box* runner;
		Box* runner2;
		ClickedMouseGoal* clickButton;
		ClickedMouseGoal* clickButton2;
};