#pragma once
#include <map>
#include "Mouse.h"
#include "Color.h"
#include <vector>

using namespace std;
class MouseManager;
class MouseManager
{
public:
	//this is probably over storing things, but eh it'll make my life easier
	map<int, Mouse*> miceDeviceMap;
	map<Color, Mouse*> miceByColor;
	vector<Mouse*> mice;
	Mouse* buildMouse(int deviceNum);
	
	void update();
	void draw();
	static MouseManager* instance;
	static MouseManager* getInstance();
private:
	Color potentialMiceColors[10];
	MouseManager();
};

