#include <vector>
#include "PolygonObject.h"
#include "Physics.h"
#include "Goal.h"
#include "MouseCage.h"
#include "LevelButton.h"
#include "MouseAssignmentButton.h"
#include "COMBox.h"
#include "Line.h"
#include "ConnectingLine.h"

#pragma once
//Wrapper class for an array with helpful methods to make things

using namespace std;
class ShapeStorage
{
public:
	b2World* world;
	ShapeStorage(b2Vec2 gravity = b2Vec2(0, -9.8));
	
	PolygonObject* operator[](int index);
	void clear();
	Goal* buildGoal(float x, float y, Color color, std::string name = "unnamed");
	Goal* buildGoal(float x, float y, float width, float height, Color color, std::string name = "unnamed");
	MouseCage* buildCage(float x, float y, Color color, std::string name = "unnamed");
	MouseCage* buildCage(float x, float y, float width, float height, Color color, std::string name = "unnamed");
	LevelButton* buildLevelButton(float x, float y, float width, float height, Color color, LevelName level, std::string name = "unnamed");
	MouseAssignmentButton* buildMouseAssignmentButton(float x, float y, float width, float height, Color color, int occupancy, std::string name = "unnamed");
	Box* AddBox(float x, float y, float mass, Color color, float height, float width, float friction = .3, float density = 1, float angle = 0, std::string name = "unnamed");
	Barrier* AddRectBarrier(float x, float y, float width, float height, float angle = 0, std::string name = "unnamed");
	COMBox* buildCOMBox(float x, float y, float width, float height, Color color,std::string name = "unnamed");

	//lines
	ConnectingLine* buildConnectingLine(Color color, int LOD, int mask, std::string name = "unnamed");
	void unload();
	void deleteObject(int index);
	void deleteObject(PolygonObject* obj);
	int count();
	PolygonObject* getObjectByName(string name);
	vector<PolygonObject*> getObjectsByTag(Tag tag);
	template<class T>
	vector<T*> getObjectOfType();
	template<class T>
	T* getObjectByNameT(string name);
	template<class T>
	vector<T*> getObjectsByTagT(Tag tag);
	vector<PolygonObject*> shapes;
	vector<Line*> lines;
	void draw();
private:
};

template<class T>
inline vector<T*> ShapeStorage::getObjectOfType()
{
	vector<T*> objs;
	for (int i = 0; i < shapes.size(); i++)
	{
		T* object = dynamic_cast<T*>(shapes[i]);
		if (object != nullptr)
		{
			objs.push_back(object);
		}
	}
	return objs;
}

template<class T>
inline T* ShapeStorage::getObjectByNameT(string name)
{
	PolygonObject* p = getObjectByName(name);
	if (p != nullptr)
	{
		return dynamic_cast<T*>(p);
	}
}

template<class T>
inline vector<T*> ShapeStorage::getObjectsByTagT(Tag tag)
{
	vector<T*> objs;
	for (int i = 0; i < shapes.size(); i++)
	{
		T* object = dynamic_cast<T*>(shapes[i]);
		if (object != nullptr && shapes[i]->hasTag(tag))
		{
			objs.push_back(object);
		}
	}

	return objs;
}
