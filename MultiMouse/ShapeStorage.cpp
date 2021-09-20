#include "ShapeStorage.h"

ShapeStorage::ShapeStorage(b2Vec2 gravity)
{
	world = new b2World(gravity);
}

PolygonObject* ShapeStorage::operator[](int index)
{
	return shapes[index];
}

void ShapeStorage::clear()
{
	shapes.clear();
}

Goal* ShapeStorage::buildGoal(float x, float y, Color color, std::string name)
{
	Goal* g = new Goal(x, y, color, name);
	shapes.push_back(g);
	return g;
}

Goal* ShapeStorage::buildGoal(float x, float y, float width, float height, Color color, std::string name)
{
	Goal* g = new Goal(x, y, color, width, height, name);
	shapes.push_back(g);
	return g;
}

MouseCage* ShapeStorage::buildCage(float x, float y, Color color, std::string name)
{
	color.a = .5f;
	MouseCage* cage = new MouseCage(x, y, color, name);
	shapes.push_back(cage);
	return cage;
}

MouseCage* ShapeStorage::buildCage(float x, float y, float width, float height, Color color, std::string name)
{
	color.a = .5f;
	MouseCage* cage = new MouseCage(x, y, width, height, color, name);
	shapes.push_back(cage);
	return cage;
}

LevelButton* ShapeStorage::buildLevelButton(float x, float y, float width, float height, Color color, LevelName level, std::string name)
{
	LevelButton* lb = new LevelButton(x, y, width, height, color, level, name);
	shapes.push_back(lb);
	return lb;
}

MouseAssignmentButton* ShapeStorage::buildMouseAssignmentButton(float x, float y, float width, float height, Color color, int occupancy, std::string name)
{
	MouseAssignmentButton* msb = new MouseAssignmentButton(x, y, width, height, color, occupancy);
	shapes.push_back(msb);
	return msb;
}

Box* ShapeStorage::AddBox(float x, float y, float mass, Color color, float height, float width, float friction, float density, float angle, std::string name)
{
	Box* box = new Box(x, y, mass, color, height, width, friction, density, angle, name);
	box->body = world->CreateBody(&box->def);
	box->body->CreateFixture(&box->fixtureDef);
	box->body->SetUserData(box);
	shapes.push_back(box);
	return box;
}

Barrier* ShapeStorage::AddRectBarrier(float x, float y, float width, float height, float angle, std::string name)
{
	Barrier* barrier = new Barrier(x, y, angle, name);
	barrier->setShapeAsBox(width, height);
	barrier->body = world->CreateBody(&barrier->def);
	barrier->body->CreateFixture(&barrier->shape, 0);
	barrier->body->SetUserData(barrier);
	shapes.push_back(barrier);
	return barrier;
}

COMBox* ShapeStorage::buildCOMBox(float x, float y, float width, float height, Color color,std::string name)
{
	COMBox* box = new COMBox(x, y, width, height,color, name);
	box->body = world->CreateBody(&box->def);
	box->body->CreateFixture(&box->fixtureDef);
	box->body->SetUserData(box);
	box->body->SetGravityScale(0);
	box->body->SetType(b2_dynamicBody);
	shapes.push_back(box);
	return box;
}

ConnectingLine* ShapeStorage::buildConnectingLine(Color color, int LOD, int mask, std::string name)
{
	ConnectingLine* line = new ConnectingLine(color, LOD, mask, name);
	lines.push_back(line);
	return line;
}

CubicBezier* ShapeStorage::buildCubicBezier(Color color, int LOD, int mask, std::string name)
{
	CubicBezier* line = new CubicBezier(color, LOD, mask, name);
	lines.push_back(line);
	return line;
}

ControlPoint* ShapeStorage::buildControlPoint(b2Vec2 position, Color color)
{
	ControlPoint* point = new ControlPoint(position, color);
	shapes.push_back(point);
	return point;
}

void ShapeStorage::unload()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
	for (int i = 0; i < lines.size(); i++)
	{
		delete lines[i];
	}
	world->~b2World();
}

void ShapeStorage::deleteObject(int index)
{
	PolygonObject* obj = shapes[index];
	PolygonPhysicsObject* object = dynamic_cast<PolygonPhysicsObject*>(obj);
	if (object != NULL)
	{
		if (object->selected != nullptr)
		{
			object->selected->releasePhysicsSelect();
		}
	
		world->DestroyBody(object->body);
	}
	shapes.erase(shapes.begin() + index);
	delete obj;
}


void ShapeStorage::deleteObject(PolygonObject* obj)
{
	PolygonPhysicsObject* object = dynamic_cast<PolygonPhysicsObject*>(obj);
	if (object != NULL)
	{

		if (object->selected != nullptr)
		{
			object->selected->releasePhysicsSelect();
		}
		world->DestroyBody(object->body);
	}
	shapes.erase(std::find(shapes.begin(), shapes.end(), obj));
	delete obj;
}

int ShapeStorage::count()
{
	return shapes.size();
}

PolygonObject* ShapeStorage::getObjectByName(string name)
{
	for (PolygonObject* obj : shapes)
	{
		if (name == obj->name)
		{
			return obj;
		}
	}
	return nullptr;
}

vector<PolygonObject*> ShapeStorage::getObjectsByTag(Tag tag)
{
	std::vector<PolygonObject*> objs;
	for (PolygonObject* p : shapes)
	{
		if (p->hasTag(tag))
		{
			objs.push_back(p);
		}
	}
	return objs;
}

void ShapeStorage::draw()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->draw();
		
	}
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->draw();
	}
}
