#ifndef IDCCALCMIDVAL_H
#define IDCCALCMIDVAL_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "idcplayerstats.h"
class IDCCalcMidVal
{
public:
    virtual double middleValue(const DCIndex &index, const int &remainingScore, const int &initialScore) const = 0;
};
#endif // IDCUPDATEMIDVAL_H
