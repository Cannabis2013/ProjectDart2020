#ifndef DCAVERAGECALC_H
#define DCAVERAGECALC_H

#include "DartsController/DCInputStatsSLAs/idcaveragecalc.h"
#include <math.h>

class DCAverageCalc : public IDCAverageCalc
{
public:
    virtual double average(DCContext::IDCInputModel *input, const IDCIndexService *indexService,
                           const IDCInitialScore *initialService) const override
    {

        auto initialScore = initialService->score();
        double totalScore =  initialScore - input->remainingScore();
        double attempts = indexService->roundIndex() * 3;
        double avg = totalScore / attempts;
        return round(avg);
    }
};
#endif // DCAVERAGECALC_H
