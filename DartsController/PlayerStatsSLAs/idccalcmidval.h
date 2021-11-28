#ifndef IDCCALCMIDVAL_H
#define IDCCALCMIDVAL_H
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
#include "DartsController/DCScoresSLAs/abstractdcscoresctx.h"
#include "idcstatscontext.h"
class IDCCalcMidVal
{
public:
    virtual double middleValue(const DCIndex &index, const int &remainingScore, const int &initialScore) const = 0;
};
#endif // IDCUPDATEMIDVAL_H
