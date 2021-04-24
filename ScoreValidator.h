#ifndef SCOREVALIDATOR_H
#define SCOREVALIDATOR_H

#include "iscorevalidator.h"

class ScoreValidator : public IScoreValidator
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
    // Create instance
    static ScoreValidator* createInstance(const int &terminalKeyCode)
    {
        return new ScoreValidator(terminalKeyCode);
    }
    // InputValidatorInterface interface
<<<<<<< Updated upstream
    virtual int validateInput(const int &currentScore) const override
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
        else if(currentScore == 0)
            return TargetDomain;
        else
            return OutsideDomain;
    }

    int terminalKeyCode() const
    {
        return _terminalKeyCode;
    }

    int maxAllowedInput() const
    {
        return _maxAllowedInput;
    }
private:
    ScoreValidator(const int &terminalKeyCode):
        _terminalKeyCode(terminalKeyCode){}
    const int _terminalKeyCode;
    const int _maxAllowedInput = 180;
};
#endif // SCOREVALIDATOR_H
