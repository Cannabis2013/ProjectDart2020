#ifndef IDCSETINPUTSTATS_H
#define IDCSETINPUTSTATS_H
#include "DartsController/PlayerStatsServices/dcplayerstatsmanager.h"
#include "idccalcmidval.h"
class IDCSetInputStats
{
public:
    virtual void set(DCInput &input, IDCPlayerStats *statsService, const IDCCalcMidVal *calcMidVal, const DCIndex &index, const int &initialScore) const = 0;
};
#endif // IDCDETSCORERANGE_H
