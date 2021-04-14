#pragma once
#include "Level.h"
class MusicalChairs :
    public Level
{
public:
    MusicalChairs();
    vector<MouseAssignmentButton*> chairs;
    Timer* roundTimer;
    int roundNum;
    bool checkForNewRound();
    void startRound();
    void update();
};

