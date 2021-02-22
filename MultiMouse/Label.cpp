#include "Label.h"

Label::Label(sf::String string, int x, int y, int size, Color textColor, sf::Font font, Color backgroundColor)
{
	text = new sf::Text();
	this->font = font;
	
	text->setString(string);
	text->setCharacterSize(size);
	text->setFillColor(sf::Color(textColor.r * 255, textColor.g * 255, textColor.b * 255, 255));
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
