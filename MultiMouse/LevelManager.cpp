#include "LevelManager.h"

LevelManager* LevelManager::instance;
LevelManager::LevelManager()
{
	currentLevel = new LevelSelect();
	reqs[LevelName::Juggling] = 2;
	reqs[LevelName::DebugLevel] = 0;
	reqs[LevelName::Pong] = -2;
	reqs[LevelName::Dodgeball] = -2;
	reqs[LevelName::Musical] = 0;
	reqs[LevelName::Maze] = -2;
	reqs[LevelName::Circus] = 0;
	reqs[LevelName::WackAMole] = 0;
	reqs[LevelName::ClickRace] = -2;
	reqs[LevelName::BasketBall] = 0;
	reqs[LevelName::BrickBreaker] = 0;

}

void LevelManager::changeLevel(LevelName newLevel)
{
	currentLevel->unload();
	MouseManager::getInstance()->unfreezeAllMice();
	MouseManager::getInstance()->resetAllLeaders();

	if (reqs[newLevel] > 0)
	{
		if (MouseManager::getInstance()->getNumOfActiveMice() > reqs[newLevel])
		{
			currentLevel = new PlayerSelect(reqs[newLevel], newLevel);
			return;
		}
	}
	else if (reqs[newLevel] < 0 && MouseManager::getInstance()->teams.size() == 0)
	{
		if (MouseManager::getInstance()->getNumOfActiveMice() >= -reqs[newLevel])
		{
			currentLevel = new TeamSelect(-reqs[newLevel], MouseManager::getInstance()->getNumOfActiveMice() / -reqs[newLevel], newLevel);
			return;
		}
	}

	switch (newLevel)
	{
	case LevelName::Juggling:
		currentLevel = new JugglingLevel();
		break;
	case LevelName::DebugLevel:
		currentLevel = new DebugLevel();
		break;
	case LevelName::Pong:
		currentLevel = new PongLevel();
		break;
	case LevelName::Dodgeball:
		currentLevel = new DodgeballLevel();
		break;
	case LevelName::Musical:
		currentLevel = new MusicalChairs();
		break;
	case LevelName::LevelSelect:
		MouseManager::getInstance()->resetMice();
		MouseManager::getInstance()->clearTeams();
		ScoreManager::getInstance()->setLeaders();
		currentLevel = new LevelSelect();
		break;
	case LevelName::Maze:
		currentLevel = new MazeLevel();
		break;
	case LevelName::Circus:
		currentLevel = new CircusLevel();
		break;
	case LevelName::CurveMatch:
		currentLevel = new CurveMatch();
		break;
	case LevelName::WackAMole:
		currentLevel = new WackAMole();
		break;
	case LevelName::ClickRace:
		currentLevel = new ClickRace();
		break;
	case LevelName::LeaderBoard:
		ScoreManager::getInstance()->setLeaders();
		currentLevel = new Leaderboard();
		break;
	case LevelName::BrickBreaker:
		currentLevel = new BrickBreaker();
		break;
	case LevelName::BasketBall:
		currentLevel = new AngryBirds();
		break;
	}
	



	currentLevel->init();
}

void LevelManager::checkChangeLevel()
{
	if (EventStorage::getInstance()->levelEvents.size() > 0)
	{
		changeLevel((LevelName)EventStorage::getInstance()->levelEvents[0]);
		EventStorage::getInstance()->levelEvents.clear();
	}
}

LevelManager* LevelManager::getInstance()
{
	if (!instance)
	{
		instance = new LevelManager();
	}
	return instance;
}
