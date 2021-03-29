#pragma once
#include "Level.h"
#include <random>
#define SFML_STATIC
#include <iostream>


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

