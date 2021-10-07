#include "EventStorage.h"


EventStorage* EventStorage::instance;
EventStorage* EventStorage::getInstance()
{
	if (instance == nullptr)
	{
		instance = new EventStorage();
	}
	return instance;
}

PolygonObject* EventStorage::pollCollisionEvent(int i)
{
	PolygonObject* obj = collisionEvents[i];
	collisionEvents.erase(collisionEvents.begin() + i);
	return obj;
}

void EventStorage::logCollisionEvent(PolygonObject* obj)
{
	//Should make it into a set really
	//sanity check, make sure we dont log the same thing 2 times
	//Dont love it, but this gets cleared every frame so it should be fine
	for (int i = 0; i < collisionEvents.size(); i++)
	{
		if (obj == collisionEvents[i])
		{
			return;
		}
	}
	//if its unique
	collisionEvents.push_back(obj);
}

