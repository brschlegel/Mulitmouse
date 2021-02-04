#include "Color.h"

Color::Color(float r, float g, float b)
{
	
	this->r = convertIfLarge(r);
	this->g = convertIfLarge(g);
	this->b = convertIfLarge(b);
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
	return Color(1,0,0);
}

Color Color::getGreen()
{
	return Color(0,1,0);
}

Color Color::getBlue()
{
	return Color(0,0,1);
}
