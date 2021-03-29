#pragma once
#define SFML_STATIC
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include <vector>
class UIData;
class UIData
{
public:
	static UIData* instance;
	static UIData* getInstance();

	std::map<sf::String, sf::Font> fonts;
	std::map<sf::String, sf::Texture*> images;
	sf::Texture* getTexture(sf::String name);
private:
	UIData();

};

