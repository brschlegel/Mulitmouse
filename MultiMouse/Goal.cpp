#include "Goal.h"


Goal::Goal(float x, float y, Color color) : Trigger(x, y, color, false, true)
{
	this->score = 0;
	triggerId = 1;
}

Goal::Goal(float x, float y, Color color, float width, float height) : Trigger(x,y,width, height,color,false,true)
{
	this->score = 0;
	triggerId = 1;
}

void Goal::onEnter(PolygonObject* object)
{
	score++;
}


//things shouldn't stay in the goal
void Goal::onStay()
{
}

