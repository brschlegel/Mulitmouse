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
	vector<vector<Mouse*>> teams;
	void setTeam(vector<Mouse*> m, Color color);
	void clearTeams();
	Mouse* buildMouse(int deviceNum);
	
	void update();
	void draw();
	void setAllMiceActive(bool cond = true);
	void unfreezeAllMice();
	int getNumOfActiveMice();
	vector<Mouse*> getActiveMice();
	static MouseManager* instance;
	static MouseManager* getInstance();
private:
	Color potentialMiceColors[10];
	MouseManager();
};

