#ifndef IDCCALCMIDVAL_H
#define IDCCALCMIDVAL_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "idcplayerstats.h"
class IDCCalcMidVal
{
public:
    virtual double middleValue(IDartsIndex *index, const int &remainingScore, const int &initialScore) const = 0;
};
#endif // IDCUPDATEMIDVAL_H
