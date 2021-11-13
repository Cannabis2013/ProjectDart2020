#ifndef IDCSETINPUTSTATS_H
#define IDCSETINPUTSTATS_H
#include "DartsController/PlayerStatsServices/dcplayerstatsmanager.h"
#include "idccalcmidval.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDCSetInputStats
{
public:
    virtual void set(AbstractDartsInput *input, IDCPlayerStats *statsService, const IDCCalcMidVal *calcMidVal, IDartsIndex *index, const int &initialScore) const = 0;
};
#endif // IDCDETSCORERANGE_H
