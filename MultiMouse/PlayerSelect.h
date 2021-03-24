#pragma once
#include "Level.h"


class PlayerSelect :
    public Level
{
public:
    vector<MouseAssignmentButton*> buttons;
    LevelName chainedLevel;
    PlayerSelect(int numButtons, LevelName chainedLevel);
    void update();
    int checkLevelUpdate();
};

