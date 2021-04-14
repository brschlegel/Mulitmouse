#pragma once
#include "Label.h"
#include <string>
class Timer :
    public Label
{
public:
    Timer(float maxTime, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor, std::string name = "unnamed");
    void draw(sf::RenderWindow* window);
    float getNumSeconds();
    void reset();
private:
    sf::Time currentTime;
    sf::Time maxTime;
    sf::Clock* clock;

};

