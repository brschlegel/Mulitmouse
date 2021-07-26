#pragma once
#include "Box.h"
class COMBox;

class COMBox :
    public Box
{
public:
    COMBox(float x, float y, float width, float height, Color color, std::string name = "unnamed");
    std::vector<Mouse*> mice;
    std::vector<float> weights;
    void updateObj();
    void setTeam(std::vector<Mouse*> mice);
    float clickIncrement;
    void normalizeWeights();
    void draw();
};

