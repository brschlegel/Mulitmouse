#pragma once
#include "Level.h"
#include "PongLevel.h"
#include "Delegate.h"



class BrickBreaker :
	public Level
{
public:
	BrickBreaker();
	void update();
	void init();
	MouseCage* bottomCage;
	Goal* ball;
	Box* brick;
	Box* paddle;
	Box* hidden;
	PongListener listener;
};