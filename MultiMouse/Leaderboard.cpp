#include "Leaderboard.h"

Leaderboard::Leaderboard()
{
	Scene* main = new Scene(standardGravity, "main");
	LevelButton* lb = main->shapes->buildLevelButton(0, -4, 2.75f, 1, Color::getGreen(), LevelName::LevelSelect);
	lb->active = true;
	main->ui.buildLabelInTrigger("Back to Level Select", lb);
	
	vector<Mouse*> mice = ScoreManager::getInstance()->setLeaders();
	for (int i = 0; i < mice.size(); i++)
	{
		main->ui.buildLabel(mice[i]->text.getString() + "): " + to_string(mice[i]->score), 0, 4 - (.5f * i), 24);
	}
	scenes["main"] = main;
	currentScene = main;
}
