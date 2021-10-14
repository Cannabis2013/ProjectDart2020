#ifndef IDCAVERAGECALC_H
#define IDCAVERAGECALC_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCInputSLAs/idcinputmodel.h"

#include "DartsController/DCMetaSLAs/idcinitialscore.h"

class IDCAverageCalc
{
public:
    virtual double average(DCContext::IDCInputModel *input, const IDCIndexService *indexService,
                           const IDCInitialScore *initialScore) const = 0;
};
#endif // IDCAVERAGECALC_H
