#pragma once
#include <vector>
class Color
{
public:
	float r, g, b, a;

	Color(float r, float g, float b, float a = 1);
	Color();
	static Color getRed();
	static Color getGreen();
	static Color getBlue();
	static std::vector<Color> getListOfColors();
	float convertIfLarge(float num);

	//needed to sort in the map
	bool operator<(const Color& rhs) const noexcept
	{
		// logic here
		return this->r < rhs.r;// for example
	}

	bool operator==(const Color& rhs)
	{
		return this->r == rhs.r && this->g == rhs.g && this->b == rhs.b && this->a == rhs.a;
	}
};

