#ifndef IDCAVERAGECALC_H
#define IDCAVERAGECALC_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCInputSLAs/idcinput.h"

#include "DartsController/DCMetaSLAs/idcinitialscore.h"

class IDCAverageCalc
{
public:
    virtual double average(IDCInput *input, const IDCIndexService *indexService,
                           const IDCInitialScore *initialScore) const = 0;
};
#endif // IDCAVERAGECALC_H
