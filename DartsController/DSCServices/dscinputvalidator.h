#ifndef DSCINPUTVALIDATOR_H
#define DSCINPUTVALIDATOR_H

#include "DartsController/DPCServices/dpcinputevaluator.h"

class DSCInputValidator : public AbstractDCInputEvaluator
{
public:
    static DSCInputValidator *createInstance()
    {
        return new DSCInputValidator();
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
