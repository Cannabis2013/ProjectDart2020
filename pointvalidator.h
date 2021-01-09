#ifndef POINTVALIDATOR_H
#define POINTVALIDATOR_H

#include "scorevalidatorinterface.h"

class PointValidator : public ScoreValidatorInterface
{
    // ScoreEvaluatorInterface interface
public:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    enum PointDomains {
        InvalidDomain = 0x02,
        PointDomain = 0x04,
        CriticalDomain = 0x06,
        OutsideDomain = 0x08,
        TargetDomain = 0xa
    };
    PointValidator(const int& terminalCondition):
        _terminalCondition(terminalCondition)
    {}
    virtual int evaluateScore(const int &currentScore,
                              const int &keyCode,
                              const int &input) const override
    {
        int minimumAllowedScore = 2;
        if(terminalCondition() == KeyMappings::SingleModifer)
            minimumAllowedScore = 1;
        else if(terminalCondition() == KeyMappings::DoubleModifier)
            minimumAllowedScore = 2;
        else
            minimumAllowedScore = 3;


        if(currentScore > criticalLimit())
            return PointDomain;
        else if(currentScore <= criticalLimit() &&
                currentScore >= minimumAllowedScore)
            return CriticalDomain;
        else if(currentScore == 0 && (keyCode == terminalCondition() ||
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
    int terminalCondition() const
    {
        return _terminalCondition;
    }
    int criticalLimit() const
    {
        return _criticalLimit;
    }
    const int _criticalLimit = 180;
    const int _terminalCondition;
    const int _bullsEye = 50;
};







#endif // POINTVALIDATOR_H
