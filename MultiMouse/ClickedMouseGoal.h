#pragma once
#include "MouseGoal.h"
class ClickedMouseGoal :
    public MouseGoal
{
public:
    int numClicks;
    ClickedMouseGoal(float x, float y, Color color, float width, float height,std::string name = "unnamed");
    void onCollision(PolygonObject* other);
    Delegate<void, Mouse*> onClickDel;
    

    
};

