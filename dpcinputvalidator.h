#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H

#include "idartsinputvalidator.h"

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
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    static DPCInputValidator* createInstance(const int& terminalKeyCode)
    {
        return new DPCInputValidator(terminalKeyCode);
    }
    virtual int validateInput(const int &currentScore,
                              const int &keyCode,
                              const int &input) const override
    {
        int minimumAllowedScore = 2;
        if(terminalKeyCode() == KeyMappings::SingleModifer)
            minimumAllowedScore = 1;
        else if(terminalKeyCode() == KeyMappings::DoubleModifier)
            minimumAllowedScore = 2;
        else
            minimumAllowedScore = 3;


        if(currentScore > maxAllowedInput())
            return PointDomain;
        else if(currentScore <= maxAllowedInput() &&
                currentScore >= minimumAllowedScore)
            return CriticalDomain;
        else if(currentScore == 0 && (keyCode == terminalKeyCode() ||
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
    DPCInputValidator(const int& terminalCondition):
        _terminalKeyCode(terminalCondition){}
    int terminalKeyCode() const
    {
        return _terminalKeyCode;
    }
    int maxAllowedInput() const
    {
        return _maxAllowedInput;
    }
    const int _maxAllowedInput = 180;
    const int _terminalKeyCode;
    const int _bullsEye = 50;
};
#endif // POINTVALIDATOR_H
