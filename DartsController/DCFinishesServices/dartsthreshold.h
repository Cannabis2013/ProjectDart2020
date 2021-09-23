#ifndef DARTSTHRESHOLD_H
#define DARTSTHRESHOLD_H

#include "dartscreateterminalthreshold.h"
#include "DartsController/DCFinishesSLAs/idartsthresholdvalues.h"

class DartsThresholds : public IDartsThresholdValues
{
public:
    DartsThresholds(const DartsCreateTerminalThreshold &thresholdService)
        :_terminalThreshold(thresholdService.threshold())
    {}
    virtual int terminalThreshold() const override
    {
        return _terminalThreshold;
    }
    virtual int upperThresholdValue() const override
    {
        return _upperThresholdValue;
    }
private:
    const int _upperThresholdValue = 110;
    const int _terminalThreshold;
};
#endif // DARTSTHRESHOLD_H
