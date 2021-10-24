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
    virtual void evaluateInput(DCInput input, IDCPlayerApproval *, AbstractDartsController *controller) override
    {
        if(input.remainingScoreCand >= minimumAllowedScore)
        {
            input.remainingScore = input.remainingScoreCand;
            controller->persistInput(input);
        }
        else if(input.remainingScoreCand == 0)
            controller->declareWinner(input);
        else
            controller->nullifyAndPersistInput(input);
    }
private:
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
