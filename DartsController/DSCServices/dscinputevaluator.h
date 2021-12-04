#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DartsController/DPCServices/dpcinputevaluator.h"
class DSCInputEvaluator : public AbstractDCInputEvaluator
{
public:
    DSCInputEvaluator(IDCMetaContext *metaInfo, AbsDCPlayersCtx *plaScoresCtx):
        AbstractDCInputEvaluator(metaInfo,plaScoresCtx){}
    virtual void evaluate(DCInput &input, const int &scoreCand) override
    {
        if(scoreCand >= minimumAllowedScore)
        {
            input.approved = true;
            input.remScore = scoreCand;
        }
        else if(scoreCand == 0)
        {
            input.approved = true;
            input.remScore = 0;
            updateWinnerMeta(input);
        }
        else
        {
            input.score = 0;
        }
    }
private:
    void updateWinnerMeta(DCInput &input) const
    {
        metaInfo()->get().winnerName = input.playerName;
        metaInfo()->get().status = metaInfo()->WinnerDeclared;
    }
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
