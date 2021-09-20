#include "BenMath.h"

 std::map<std::pair<int, int>, int> BenMath::computedValues;
int BenMath::binomialCoefficients(std::pair<int, int> val)
{
    std::map<std::pair<int, int>, int>::iterator itr = computedValues.find(val);
    if (itr != computedValues.end())
    {
        return itr->second;
    }
    //safeguard
    if (val.second > val.first)
    {
        return 0;
    }
    if (val.second == 0 || val.first == val.second)
    {
        return 1;
    }
    int coeff = binomialCoefficients(std::make_pair(val.first - 1, val.second - 1)) + binomialCoefficients(std::make_pair(val.first - 1, val.second));
    computedValues[val] = coeff;
    return coeff;
}

int BenMath::binomialCoefficients(int n, int k)
{

    return binomialCoefficients(std::make_pair(n, k));
}
