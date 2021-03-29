#pragma once
#include "Trigger.h"
#include <vector>
#include "Mouse.h"
class MouseAssignmentButton :
    public Trigger
{
public:
    std::vector<Mouse*> mice;
    int occupancy;
    MouseAssignmentButton(float x, float y, float width, float height, Color color, int occupancy);
    void draw();
    void addMouse(Mouse* m);
    bool checkFull();
};

