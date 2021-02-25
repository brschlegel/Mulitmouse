#include "Goal.h"


Goal::Goal(float x, float y, Color color, std::string name) : Trigger(x, y, color, false, true, name)
{
	this->score = 0;
	triggerId = 1;
}

Goal::Goal(float x, float y, Color color, float width, float height, std::string name) : Trigger(x,y,width, height,color,false,true,name)
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

