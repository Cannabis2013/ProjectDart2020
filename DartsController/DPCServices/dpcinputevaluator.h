#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H
#include "DartsController/DCInputSLAs/abstractdcinputevaluator.h"
class DPCInputEvaluator : public AbstractDCInputEvaluator
{
    Q_OBJECT
public:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    static DPCInputEvaluator* createInstance()
    {
        return new DPCInputEvaluator;
    }
    virtual void evaluateInput(DCInput input, AbstractDartsController *controller, IDCWinnerService *winnerService,
                               IDCStatus *controllerStatus, const IDartsStatusCodes *statusCodes,
                               IDCPlayerController *allowancesContext) override
    {
        if(!allowancesContext->isAllowedEntrance(input.playerId))
        {
            if(input.modKeyCode == DoubleModifier)
            {
                input.remainingScore = input.remainingScoreCand;
                allowancesContext->playerIsIn(input.playerId);
            }
            else
            {
                input.score = 0;
                controller->persistInput(input);
                return;
            }
        }
        if(input.remainingScoreCand >= minimumAllowedScore)
        {
            input.remainingScore = input.remainingScoreCand;
            controller->persistInput(input);
        }
        else if(input.remainingScoreCand == 0 && (input.modKeyCode == DoubleModifier || input.score == _bullsEye))
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
            return;
        }
    }
private:
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
