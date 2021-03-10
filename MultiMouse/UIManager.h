#pragma once

#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "Label.h"
#include <map>
#include "Timer.h"
#include <vector>
class UIManager
{
public:
	std::map<sf::String, sf::Font> fonts;
	UIManager();
	void draw(sf::RenderWindow* window);
	std::vector<Label*> labels;
	Label* getLabelByName(std::string name);
	void unload();

};

