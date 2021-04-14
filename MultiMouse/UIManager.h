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
#include "UIData.h"
class UIManager
{
public:

	UIManager();
	void draw(sf::RenderWindow* window);
	std::vector<Label*> labels;
	Label* getLabelByName(std::string name);
	void unload();
	sf::Vector2<int> convertWorldToUICoords(float x, float y);
	sf::Vector2i converWorldToUIDim(float width, float height);
	Label* buildLabelInTrigger(std::string string, PolygonObject* obj, int size = 24 ,sf::String fontName = "MainFont", Color color = Color(0, 0, 0, 1), std::string name = "unnamed");
	Label* buildLabel(std::string string,float x, float y, int size, sf::String fontName = "MainFont", Color color = Color(0, 0, 0, 1), std::string name = "unnamed");
	Timer* buildTimer(float maxTime, int x, int y, int size, std::string fontName = "MainFont", Color color = Color(0, 0, 0, 1), std::string name = "unnamed");
	float getWidthOfText(sf::String string, int size, sf::String fontName = "MainFont");
	sf::String fitInBox(sf::String string, int size, float width, sf::String fontname = "MainFont");
	sf::Sprite* buildSprite(sf::String imageName, float x, float y, float width, float height);
	std::vector<Timer*> getTimers();
	int SCREENWIDTH, SCREENHEIGHT;
	std::vector<sf::Sprite*> sprites;

};

