#ifndef DSCUPDATEMIDVAL_H
#define DSCUPDATEMIDVAL_H
#include "DartsController/PlayerStatsSLAs/idcupdatemidval.h"
class DSCUpdateMidVal : public IDCUpdateMidVal
{
public:
    virtual double middleValue(const DCIndex &index, const int &remainingScore, const IDCInitialScore *initialScore) const override
    {
        auto initial = initialScore->score();
        auto scoresAccumulated = initial - remainingScore;
        auto roundIndex = index.roundIndex;
        return scoresAccumulated/roundIndex;
    }
};
#endif // DSCCALCMIDDLEVAL_H
