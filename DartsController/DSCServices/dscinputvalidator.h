#ifndef DSCINPUTVALIDATOR_H
#define DSCINPUTVALIDATOR_H

#include "DartsController/DPCServices/dpcinputvalidator.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"

class DSCInputValidator : public IDartsInputValidator
{
public:
    enum InputDomains {
        PointDomain = 0x01,
        CriticalDomain = 0x02,
        OutsideDomain = 0x03,
        TargetDomain = 0x4,
        InputOutOfRange = 0x5
    };
    static DSCInputValidator *createInstance()
    {
        return new DSCInputValidator();
    }
    virtual int validateInput(const int &currentScore,
                              const IDCInputKeyCodes *,
                              const int &, const int &) const override
    {
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
private:
    int maxAllowedInput() const
    {
        return _maxAllowedInput;
    }
    const int _maxAllowedInput = 180;
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
