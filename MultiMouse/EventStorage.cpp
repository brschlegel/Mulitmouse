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

