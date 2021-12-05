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
		if (mice[i]->score == top && top != 0)
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

float ScoreManager::getHighScore(string name)
{
	ifstream f("Highscores/" + name + ".txt");
	//create file if it doesn't exist
	if (!f.is_open())
	{
		ofstream file("Highscores / " + name + ".txt");
		file.close();
		return 0;
	}
	//yeah its ugly
	ifstream file("Highscores/" + name + ".txt");
	string line;

	getline(file, line);
	file.close();
	return stof(line);
}

void ScoreManager::setHighScore(string name, float value)
{
	//overwrite file
	ofstream file("Highscores/" + name + ".txt", std::ios::trunc);
	file << to_string(value);
	file.close();
}

