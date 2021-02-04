#pragma once


class Color
{
public:
	float r, g, b;

	Color(float r, float g, float b);
	static Color getRed();
	static Color getGreen();
	static Color getBlue();
	float convertIfLarge(float num);
};

