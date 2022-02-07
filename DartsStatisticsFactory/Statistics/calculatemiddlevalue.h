#ifndef CALCULATEMIDDLEVALUE_H
#define CALCULATEMIDDLEVALUE_H
#include "StatsServices/CalcAverage/ICalcAverage.h"
class CalculateMiddleValue : public ICalcAverage
{
public:
    virtual double middleValue(const int &accumulatedScore, const int &n) const override;
};

#endif // CALCULATEMIDDLEVALUE_H
