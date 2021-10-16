#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H

#include "DartsController/DCInputSLAs/abstractevaluatedcinput.h"

class DPCInputValidator : public AbstractEvaluateDCInput
{
    Q_OBJECT
public:
    static DPCInputValidator* createInstance()
    {
        return new DPCInputValidator;
    }
    virtual void validateInput(const int &remainingScore, const IDCInputKeyCodes *keyCodes,
                               IDCInput *input, IDCPlayerApproval *approvalContext) override
    {
        if(!approvalContext->isAllowedEntrance(input->playerId()))
        {
            if(input->modKeyCode() == keyCodes->doubleModifier())
                approvalContext->playerIsIn(input->playerId());
            else
            {
                emit playerOutOfRange(input);
                return;
            }
        }
        if(remainingScore >= minimumAllowedScore)
            emit playerHitPointDomain(input);
        else if(remainingScore == 0)
        {
            if(input->modKeyCode() == keyCodes->doubleModifier() || input->score() == bullsEye())
                emit playerHitTargetDomain(input);
            else
                emit playerOutOfRange(input);
        }
        else
            emit playerOutOfRange(input);
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
