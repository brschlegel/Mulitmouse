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
#include "PolygonObject.h"
class UIManager
{
public:
	std::map<sf::String, sf::Font> fonts;
	UIManager();
	void draw(sf::RenderWindow* window);
	std::vector<Label*> labels;
	Label* getLabelByName(std::string name);
	void unload();
	sf::Vector2<int> convertWorldToUI(float x, float y);
	Label* buildLabelInTrigger(std::string string, PolygonObject* obj, sf::String fontName = "MainFont", Color color = Color(0, 0, 0, 1), std::string name = "unnamed");
	int SCREENWIDTH, SCREENHEIGHT;

};

