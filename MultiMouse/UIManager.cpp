#include "UIManager.h"




UIManager::UIManager()
{
	sf::Font font;
	font.loadFromFile("fonts/Main.ttf");
	fonts["MainFont"] = font;
	labels.push_back(new Timer(30, 20, 20, 24, Color::getRed(), fonts["MainFont"], Color::getBlue()));
}

void UIManager::draw(sf::RenderWindow* window)
{
	window->pushGLStates();
	window->resetGLStates();


	
	for (int i = 0; i < labels.size(); i++)
	{
		labels[i]->draw(window);
	}
	
	window->popGLStates();
}
