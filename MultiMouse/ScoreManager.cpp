#include "ScoreManager.h"

ScoreManager* ScoreManager::instance;


ScoreManager::ScoreManager()
{
	
}

ScoreManager* ScoreManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ScoreManager();
	}
	return instance;
} 

vector<Mouse*> ScoreManager::setLeaders()
{
	vector<Mouse*> mice(MouseManager::getInstance()->mice);
	std::sort(mice.begin(), mice.end(), [](const Mouse* a, const Mouse* b) {return a->score > b->score; });
	float top = mice[0]->score;
	for (int i = 0; i < mice.size(); i++)
	{
		if (mice[i]->score == top)
		{
			mice[i]->isLeader = true;
		}
		else
		{
			mice[i]->isLeader = false;
		}
	}

	return mice;

}


void ScoreManager::incrementScore(Mouse* mouse, int amount)
{
	mouse->score += amount;
}

void ScoreManager::incrementScoreTeam(vector<Mouse*> mice, int amount)
{
	for (int i = 0; i < mice.size(); i++)
	{
		incrementScore(mice[i], amount);
	}
}

bool ScoreManager::compareMice(const Mouse* a, const Mouse* b)
{
	return a->score > b->score;
}

