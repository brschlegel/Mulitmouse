#include "ClickedMouseGoal.h"

ClickedMouseGoal::ClickedMouseGoal(float x, float y, Color color, float width, float height, std::string name) : MouseGoal(x,y,color,width,height,name)
{

}

void ClickedMouseGoal::onCollision(PolygonObject* other)
{
	Mouse* mouse = dynamic_cast<Mouse*>(other);
	if (mouse != nullptr && mouse->leftButtonPressed && !mouse->prevLeft)
	{
		numClicks++;
	}

}
