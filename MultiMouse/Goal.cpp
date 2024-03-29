#include "Goal.h"


Goal::Goal(float x, float y, Color color, std::string name) : Trigger(x, y, color,4,name)
{
	this->score = 0;
	triggerId = 1;
}

Goal::Goal(float x, float y, Color color, float width, float height, std::string name) : Trigger(x,y,width, height,color,4,name)
{
	this->score = 0;
	triggerId = 1;
}

Goal::Goal(float x, float y, Color color, float width, float height, int mask, std::string name) : Trigger(x, y, width, height, color, mask, name)
{
}

void Goal::onEnter(PolygonObject* object)
{
	score++;
	onColDel.ExecuteIfBound(object);
}


//things shouldn't stay in the goal
void Goal::onStay()
{
}



void Goal::onCollision(PolygonObject* other)
{
	
	if (!other->hasTag(Tag::Unscorable))
	{
		onEnter(other);
		//Delete the object
		EventStorage::getInstance()->logCollisionEvent(other);
	}
}

