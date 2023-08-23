#ifndef DARTSSTATSSERVICES_H
#define DARTSSTATSSERVICES_H

#include "CalcAverage/ICalcAverage.h"

#include <DartsStatistics/Contracts/StatsServices/ScoreRange/iupdatescorerange.h>

struct PlayerStats;
class IMirrorsDb;
struct SnapShot;

class StatsServices
{
public:
        typedef IUpdateScoreRange<SnapShot,PlayerStats> UpdateScoreRange;
    ICalcAverage *calcAverage() const {return _calcAverage;}
    void setCalcAverage(ICalcAverage *newCalcAverage) {_calcAverage = newCalcAverage;}
    UpdateScoreRange *updateScoreRange() const {return _updateScoreRange;}
    void setUpdateScoreRange(UpdateScoreRange *newUpdateScoreRange) {_updateScoreRange = newUpdateScoreRange;}
private:
    ICalcAverage *_calcAverage;
    UpdateScoreRange *_updateScoreRange;
};
#endif // STATSSERVICES_H
