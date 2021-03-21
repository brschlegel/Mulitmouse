#pragma once
class Color
{
public:
	float r, g, b, a;

	Color(float r, float g, float b, float a = 1);
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

