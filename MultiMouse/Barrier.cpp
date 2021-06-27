#include "Barrier.h"

Barrier::Barrier(float x, float y, float angle, std::string name) : PolygonPhysicsObject(x, y, 0, Color(147.0f, 140.0f, 140.0f), 0, angle, name)
{
	addTag(Tag::Unscorable);
}
