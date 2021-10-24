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
    virtual void evaluateInput(DCInput input,  IDCPlayerApproval *approvalContext, AbstractDartsController *controller) override
    {
        if(!approvalContext->isAllowedEntrance(input.playerId))
        {
            if(input.modKeyCode == DoubleModifier)
            {
                input.remainingScore = input.remainingScoreCand;
                approvalContext->playerIsIn(input.playerId);
            }
            else
            {
                controller->nullifyAndPersistInput(input);
                return;
            }
        }
        if(input.remainingScoreCand >= minimumAllowedScore)
        {
            input.remainingScore = input.remainingScoreCand;
            controller->persistInput(input);
        }
        else if(input.remainingScoreCand == 0 && (input.modKeyCode == DoubleModifier || input.score == _bullsEye))
            controller->declareWinner(input);
        else
            controller->nullifyAndPersistInput(input);
    }
private:
    const int _maxAllowedInput = 180;
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
