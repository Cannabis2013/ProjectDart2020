#ifndef DARTSCONSTRUCTSERVICES_H
#define DARTSCONSTRUCTSERVICES_H
#include <idartsattemptvalues.h>
#include "idartsfieldvalues.h"
#include "idartsthresholdvalues.h"
#include "idartsboundaries.h"
#include "idartsdivisorvalues.h"
#include "idartsterminaldivisor.h"
class DartsConstructServices
{
public:
    IDartsAttemptValues *attempts() const
    {
        return _attemptValues;
    }
    void setAttemptsService(IDartsAttemptValues *service)
    {
        _attemptValues = service;
    }

    IDartsBoundaries *boundaries() const
    {
        return _boundaries;
    }
    void setBoundariesService(IDartsBoundaries *newBoundaries)
    {
        _boundaries = newBoundaries;
    }

    IDartsFieldValues *fieldValues() const
    {
        return _fieldValues;
    }
    void setFieldValuesService(IDartsFieldValues *newFieldValues)
    {
        _fieldValues = newFieldValues;
    }

    IDartsThresholdValues *thresholds() const
    {
        return _threshold;
    }
    void setThresholdsService(IDartsThresholdValues *service)
    {
        _threshold = service;
    }
    IDartsDivisorValues *divisors() const
    {
        return _divisors;
    }
    void setDivisorsService(IDartsDivisorValues *service)
    {
        _divisors = service;
    }
    IDartsterminalDivisor *terminalDivisor() const
    {
        return _terminalDivisor;
    }
    void setTerminalDivisor(IDartsterminalDivisor *newTerminalDivisor)
    {
        _terminalDivisor = newTerminalDivisor;
    }
private:
    IDartsAttemptValues *_attemptValues;
    IDartsBoundaries *_boundaries;
    IDartsFieldValues *_fieldValues;
    IDartsThresholdValues *_threshold;
    IDartsDivisorValues *_divisors;
    IDartsterminalDivisor *_terminalDivisor;
};
#endif // DARTSCONSTRUCTSERVICES_H
