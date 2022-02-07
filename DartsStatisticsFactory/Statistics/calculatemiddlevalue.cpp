#include "calculatemiddlevalue.h"

double CalculateMiddleValue::middleValue(const int &accumulatedScore, const int &n) const
{
    auto middleValue = accumulatedScore / n;
    int quantizedValue = middleValue * 100;
    double roundedValue = (double) quantizedValue / 100;
    return roundedValue;
}
