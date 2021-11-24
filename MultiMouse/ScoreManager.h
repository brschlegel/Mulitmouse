#pragma once

#include <map>
#include <vector>
#include "MouseManager.h"
using namespace std;
class ScoreManager;
class ScoreManager{
public:
	ScoreManager();
	static ScoreManager* instance;
	static ScoreManager* getInstance();
	map<Mouse*, int> scores;
	vector<Mouse*> leaders;
	vector<Mouse*> setLeaders();
	void incrementScore(Mouse* mouse, int amount = 1);
	void incrementScoreTeam(vector<Mouse*> mice, int amount = 1);
	bool compareMice(const Mouse* a, const Mouse* b);
	bool drawCrown = false;
};

