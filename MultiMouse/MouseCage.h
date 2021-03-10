#pragma once
#include "Trigger.h"
#include "Mouse.h"
class MouseCage :
    public Trigger
{
public:
    MouseCage(float x, float y, Color color, std::string name);
    MouseCage(float x, float y, float width, float height, Color color, std::string name);
    std::vector<Mouse*> mice;
    void draw();
    void onStay();
    void AddMouse(Mouse* mouse);
    void init();
};

