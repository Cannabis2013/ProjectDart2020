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
    virtual void evaluateInput(DCInput input, AbstractDartsController *controller, IDCWinnerService *winnerService,
                               IDCStatus *controllerStatus, const IDartsStatusCodes *statusCodes,
                               IDCPlayerController *) override
    {
        if(input.remainingScoreCand >= minimumAllowedScore)
        {
            input.remainingScore = input.remainingScoreCand;
            controller->persistInput(input);
        }
        else if(input.remainingScoreCand == 0)
        {
            input.remainingScore = 0;
            winnerService->setWinner(input);
            controllerStatus->set(statusCodes->winnerFound());
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
