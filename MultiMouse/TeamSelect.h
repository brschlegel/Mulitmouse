#pragma once
#include "Level.h"
class TeamSelect :
    public Level
{
public:
    vector<MouseAssignmentButton*> buttons;
    LevelName chainedLevel;
    TeamSelect(int numButtons, int perTeam, LevelName chainedLevel);
    void update();
    int checkLevelUpdate();

};

