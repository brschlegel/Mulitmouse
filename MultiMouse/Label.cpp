#include "Label.h"
#include <iostream>

Label::Label(sf::String string, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor, std::string name) : GameObject(x, y, name)
{
	text = new sf::Text();
	this->font = font;
	
	text->setString(string);
	text->setCharacterSize(size);
	text->setFont(font);
	text->setFillColor(sf::Color(textColor.r * 255, textColor.g * 255, textColor.b * 255, 255));
	sf::FloatRect textRect = text->getLocalBounds();

	text->setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	//right now coordinates are in screen space. this is fine, but I should really put them in the world space at somepoint
	text->setPosition(x, y);
}

void Label::draw(sf::RenderWindow* window)
{
	//need to reset font pointer every time for some stupid reason
	
	text->setFont(font);
	window->draw(*text);
	sf::RectangleShape background(sf::Vector2f(text->getLocalBounds().width, text->getLocalBounds().height));
	background.setFillColor(sf::Color::Black);

}

//This is to appease the gameobject abstract draw. Messy ik
void Label::draw()
{
}

void Label::SetString(std::string string)
{
	text->setFont(font);
	text->setString(string);
	sf::FloatRect textRect = text->getLocalBounds();

	text->setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text->setPosition(x, y);

}
