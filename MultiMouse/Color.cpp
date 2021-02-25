#include "Color.h"

Color::Color(float r, float g, float b, float a)
{
	this->r = convertIfLarge(r);
	this->g = convertIfLarge(g);
	this->b = convertIfLarge(b);
	this->a = convertIfLarge(a);
}

//gives a test pink as a default
Color::Color()
{
	this->r = convertIfLarge(255.0f);
	this->g = convertIfLarge(0.0f);
	this->b = convertIfLarge(179.0f);
	this->a = 1;
}

//Converts the value to between 0 and 1 if its in rgb
float Color::convertIfLarge(float num)
{
	if (num > 1.0f)
	{
		return num / 255.0f;
	}
	return num;
}


Color Color::getRed()
{
	return Color(255, 49, 31);
}

Color Color::getGreen()
{
	return Color(58, 204, 45);
}

Color Color::getBlue()
{
	return Color(31, 147, 255);
}
