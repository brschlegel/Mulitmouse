#pragma once
#include<Level.h>

class AngryBirds :
	public Level
{
public:
	AngryBirds();
	//vector<Mouse
	MouseCage* leftCage;
	void update();
	void init();
	Goal* basket;
	Box* ball;
};