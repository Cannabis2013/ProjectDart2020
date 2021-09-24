#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H

#include "DartsController/DCInputSLAs/idartsinputvalidator.h"

class DPCInputValidator : public IDartsInputValidator
{
public:
    enum InputDomains {
        PointDomain = 0x01,
        CriticalDomain = 0x02,
        OutsideDomain = 0x03,
        TargetDomain = 0x4,
        InputOutOfRange = 0x5
    };
    static DPCInputValidator* createInstance()
    {
        return new DPCInputValidator;
    }
    virtual int validateInput(const int &currentScore,
                              const IDCInputKeyCodes *keyCodes,
                              const int &keyCode,
                              const int &input) const override
    {
        if(currentScore > maxAllowedInput())
            return PointDomain;
        else if(currentScore <= maxAllowedInput() &&
                currentScore >= minimumAllowedScore)
            return CriticalDomain;
        else if(currentScore == 0 && (keyCode == keyCodes->doubleModifier() ||
                                      input == bullsEye()))
            return TargetDomain;
        else
            return OutsideDomain;
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
