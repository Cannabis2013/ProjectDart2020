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
    virtual void validateInput(const int &currentScore, const IDCInputKeyCodes *keyCodes, DCContext::IDCInputModel *input) override
    {
        if(currentScore >= minimumAllowedScore)
            emit playerHitPointDomain(input);
        else if(currentScore == 0)
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
