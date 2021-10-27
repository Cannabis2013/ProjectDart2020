#ifndef DPCUPDATEMIDVAL_H
#define DPCUPDATEMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idcupdatemidval.h"
class DPCUpdateMidVal : public IDCUpdateMidVal
{
public:
    virtual double middleValue(const DCIndex &index, const int &remainingScore, const IDCInitialScore *initialScore) const override
    {
        auto scoresAccumulated = initialScore->score() - remainingScore;
        auto divisor = index.roundIndex*3 + index.attemptIndex - 2;
        return scoresAccumulated/divisor;
    }
};

#endif // DPCUPDATEMIDVAL_H
