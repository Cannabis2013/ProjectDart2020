#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DartsController/DPCServices/dpcinputevaluator.h"
class DSCInputEvaluator : public AbstractDCInputEvaluator
{
public:
    static DSCInputEvaluator *createInstance()
    {
        return new DSCInputEvaluator();
    }
    virtual void evaluate(DCIptVals &input, const int &scoreCand, IDCMetaCtx *metaInfo, AbstractDartsCtrl *controller,
                          const IDartsStatusCodes *statusCodes, IDCPlayerCtx *) override
    {
        if(scoreCand >= minimumAllowedScore)
        {
            input.approved = true;
            input.remainingScore = scoreCand;
            controller->addInputToModelsContext(input);
        }
        else if(scoreCand == 0)
        {
            input.approved = true;
            input.remainingScore = 0;
            updateWinnerMeta(input,metaInfo,statusCodes);
            controller->addInputToModelsContext(input);
        }
        else
        {
            input.score = 0;
            controller->addInputToModelsContext(input);
        }
    }
private:
    void updateWinnerMeta(DCIptVals &input, IDCMetaCtx *metaInfo, const IDartsStatusCodes *statusCodes) const
    {
        metaInfo->get().winnerId = input.playerId;
        metaInfo->get().winnerName = input.playerName;
        metaInfo->get().status = statusCodes->winnerFound();
    }
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
