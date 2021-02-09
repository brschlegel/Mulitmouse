#pragma once


class Color
{
public:
	float r, g, b;

	Color(float r, float g, float b);
	Color();
	static Color getRed();
	static Color getGreen();
	static Color getBlue();
	float convertIfLarge(float num);

	//needed to sort in the map
	bool operator<(const Color& rhs) const noexcept
	{
		// logic here
		return this->r < rhs.r;// for example
	}
};

