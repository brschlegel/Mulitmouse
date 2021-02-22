#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "Color.h"

class Label
{

public:
	sf::Text* text;
	sf::Font font;
	Label(sf::String string, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor);
	void virtual draw(sf::RenderWindow* window);
};

