#ifndef DARTSSTATSSERVICES_H
#define DARTSSTATSSERVICES_H
#include "CalcAverage/ICalcAverage.h"
#include "StatsServices/ScoreRange/iupdatescorerange.h"
class CurrentStats;
class Input;
class StatsServices
{
public:
    typedef IUpdateScoreRange<Input,CurrentStats> UpdateScoreRange;
    ICalcAverage *calcAverage() const {return _calcAverage;}
    void setCalcAverage(ICalcAverage *newCalcAverage) {_calcAverage = newCalcAverage;}
    UpdateScoreRange *updateScoreRange() const {return _updateScoreRange;}
    void setUpdateScoreRange(UpdateScoreRange *newUpdateScoreRange) {_updateScoreRange = newUpdateScoreRange;}
private:
    ICalcAverage *_calcAverage;
    UpdateScoreRange *_updateScoreRange;
};
#endif // STATSSERVICES_H
