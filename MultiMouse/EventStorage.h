#pragma once
#include <utility>
#include <vector>
#include <PolygonObject.h>
class EventStorage;
using namespace std;
class EventStorage
{
public:
	vector<int> levelEvents;
	vector<PolygonObject*> collisionEvents;
	static EventStorage* getInstance();
	PolygonObject* pollCollisionEvent(int i);
private:
	static EventStorage* instance;
};

