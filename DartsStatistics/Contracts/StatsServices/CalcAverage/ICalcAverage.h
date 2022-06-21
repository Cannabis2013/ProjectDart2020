#ifndef ICALCAVERAGE_H
#define ICALCAVERAGE_H
class ICalcAverage
{
public:
    virtual double middleValue(const int &accumulatedScore, const int &n) const = 0;
};

#endif // ICALCAVERAGE_H
