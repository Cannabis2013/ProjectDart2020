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
    virtual void evaluate(DCInput input, IDCMetaInfo *metaInfo, AbstractDartsController *controller,
                               const IDartsStatusCodes *statusCodes, IDCPlayerController *) override
    {
        if(input.remainingScoreCand >= minimumAllowedScore)
        {
            input.approved = true;
            input.remainingScore = input.remainingScoreCand;
            controller->persistInput(input);
        }
        else if(input.remainingScoreCand == 0)
        {
            input.approved = true;
            input.remainingScore = 0;
            metaInfo->get().winnerId = input.playerId;
            metaInfo->get().winnerName = input.playerName;
            metaInfo->get().status = statusCodes->winnerFound();
            controller->persistInput(input);
        }
        else
        {
            input.score = 0;
            controller->persistInput(input);
        }
    }
private:
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
