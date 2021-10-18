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
    virtual void evaluateInput(const int &remainingScore, DCInput input,  IDCPlayerApproval *approvalContext, AbstractDartsController *controller) override
    {
        if(!approvalContext->isAllowedEntrance(input.playerId))
        {
            if(input.modKeyCode == DoubleModifier)
                approvalContext->playerIsIn(input.playerId);
            else
            {
                controller->nullifyAndPersistInput(input);
                return;
            }
        }
        if(remainingScore >= minimumAllowedScore)
            controller->persistInput(input);
        else if(remainingScore == 0)
        {
            if(input.modKeyCode == DoubleModifier || input.score == bullsEye())
                controller->declareWinner(input);
            else
                emit playerOutOfRange(input);
        }
        else
            controller->nullifyAndPersistInput(input);
    }
    int bullsEye() const
    {
        return _bullsEye;
    }
private:
    int maxAllowedInput() const
    {
        return _maxAllowedInput;
    }
    const int _maxAllowedInput = 180;
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
