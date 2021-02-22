#pragma once
#include "Label.h"
#include <string>
class Timer :
    public Label
{
public:
    sf::Time currentTime;
    sf::Time maxTime;
    sf::Clock* clock;
    Timer(float maxTime, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor);
    void draw(sf::RenderWindow* window);

};

