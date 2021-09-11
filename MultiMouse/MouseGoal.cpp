#include "MouseGoal.h"

MouseGoal::MouseGoal(float x, float y, Color color, float width, float height, std::string name) : Goal(x,y,color, width, height,1 , name)
{
}

void MouseGoal::onCollision(PolygonObject* other)
{
	Mouse* mouse = dynamic_cast<Mouse*>(other);
	if (mouse != nullptr && !mouse->frozen)
	{
		mice.push_back(mouse);
		mouse->frozen = true;
	}

}
