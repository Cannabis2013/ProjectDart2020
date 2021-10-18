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
    virtual void evaluateInput(const int &currentScore, DCInput input, IDCPlayerApproval *, AbstractDartsController *controller) override
    {
        if(currentScore >= minimumAllowedScore)
            controller->persistInput(input);
        else if(currentScore == 0)
            controller->declareWinner(input);
        else
            controller->nullifyAndPersistInput(input);
    }
private:
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
