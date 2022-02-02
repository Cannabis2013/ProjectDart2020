#ifndef DARTSSTATSSERVICES_H
#define DARTSSTATSSERVICES_H
#include "CalcAverage/ICalcAverage.h"
class StatsServices
{
public:
    ICalcAverage *calcAverage() const {return _calcAverage;}
    void setCalcAverage(ICalcAverage *newCalcAverage) {_calcAverage = newCalcAverage;}
private:
    ICalcAverage *_calcAverage;
};
#endif // STATSSERVICES_H
