#ifndef IDCAVERAGECALC_H
#define IDCAVERAGECALC_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCInputServices/dcinput.h"

class IDCAverageCalc
{
public:
    virtual double average(const DCInput &input, const IDCIndexService *indexService,
                           const IDCInitialScore *initialScore) const = 0;
};
#endif // IDCAVERAGECALC_H
