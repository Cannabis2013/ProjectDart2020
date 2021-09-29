#ifndef DSCINPUTVALIDATOR_H
#define DSCINPUTVALIDATOR_H

#include "DartsController/DPCServices/dpcinputvalidator.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"

class DSCInputValidator : public AbstractEvaluateDCInput
{
public:
    static DSCInputValidator *createInstance()
    {
        return new DSCInputValidator();
    }
    virtual void validateInput(const int &currentScore,
                              const IDCInputKeyCodes *, DCContext::IDCInputModel *input) override
    {
        if(currentScore >= minimumAllowedScore)
            emit playerHitPointDomain(input);
        else if(currentScore == 0)
            emit playerHitTargetDomain(input);
        else
            emit playerOutOfRange(input);
    }
private:
    int maxAllowedInput() const
    {
        return _maxAllowedInput;
    }
    const int _maxAllowedInput = 180;
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
