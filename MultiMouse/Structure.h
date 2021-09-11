#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ShapeStorage.h>
using namespace std;
class Structure
{
public:
	Structure(string filePath, float unitScale);
	float width;
	float height;
	float unitScale;
	vector<vector<char>> arr;
	void buildStructure(ShapeStorage* storage, b2Vec2 origin);
	vector<PolygonObject*> objects;
		
};

