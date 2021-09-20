#pragma once
#include <map>
static class BenMath
{
	static std::map<std::pair<int, int>, int> computedValues;
	static int binomialCoefficients(std::pair<int, int> val);
public:
	static int binomialCoefficients(int n, int k);
};

