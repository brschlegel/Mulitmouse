#include "UIManager.h"




UIManager::UIManager()
{
	sf::Font font;
	font.loadFromFile("fonts/Main.ttf");
	fonts["MainFont"] = font;
	//labels.push_back(new Timer(30, 20, 20, 24, Color::getRed(), fonts["MainFont"], Color::getBlue()));
	SCREENWIDTH = sf::VideoMode::getDesktopMode().width;
	SCREENHEIGHT = sf::VideoMode::getDesktopMode().height;
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

Label* UIManager::getLabelByName(std::string name)
{
	for (Label* label : labels)
	{
		if(label->name == name )
			return label;
	}
	return nullptr;
}

void UIManager::unload()
{
	for (int i = 0; i < labels.size(); i++)
	{
		delete labels[i];
	}
}

sf::Vector2<int> UIManager::convertWorldToUI(float x, float y)
{
	int newX = (SCREENWIDTH / (8.8889 * 2)) * x + (SCREENWIDTH / 2);
	int newY = (SCREENHEIGHT / 10.0f) * -y + (SCREENHEIGHT / 2);

	return sf::Vector2<int>(newX, newY);
}

Label* UIManager::buildLabelInTrigger (std::string string, PolygonObject* obj,sf::String fontName, Color color , std::string name)
{
	sf::Vector2i vec = convertWorldToUI(obj->x * 2, obj->y * 2);
	Label* l = new Label(string, vec.x, vec.y, 24, color, fonts[fontName], Color::getBlue(), name);
	labels.push_back(l);
	return l;
}
