#ifndef DARTSCONSTRUCTSERVICES_H
#define DARTSCONSTRUCTSERVICES_H
#include "DartsController/DCFinishesSLAs/idartsfieldvalues.h"
#include "DartsController/DCFinishesSLAs/idartsthresholdvalues.h"
#include "DartsController/DCFinishesSLAs/idartsboundaries.h"
#include "DartsController/DCFinishesSLAs/idartsdivisorvalues.h"
#include "DartsController/DCFinishesSLAs/idartsterminaldivisor.h"
#include "DartsController/DCFinishesSLAs/idartsmodidentifiers.h"
#include "idartsattemptsservice.h"
class DartsConstructServices
{
public:
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
    void setTerminalDivisorService(IDartsterminalDivisor *newTerminalDivisor)
    {
        _terminalDivisor = newTerminalDivisor;
    }
    IDartsModIdentifiers *identifiers() const
    {
        return _identifiers;
    }
    void setIdentifiersService(IDartsModIdentifiers *newIdentifiers)
    {
        _identifiers = newIdentifiers;
    }
    IDartsAttemptsService *attemptsService() const
    {
        return _attempts;
    }
    void setAttemptsService(IDartsAttemptsService *newAttempts)
    {
        _attempts = newAttempts;
    }
private:
    IDartsBoundaries *_boundaries;
    IDartsFieldValues *_fieldValues;
    IDartsThresholdValues *_threshold;
    IDartsDivisorValues *_divisors;
    IDartsterminalDivisor *_terminalDivisor;
    IDartsModIdentifiers *_identifiers;
    IDartsAttemptsService *_attempts;
};
#endif // DARTSCONSTRUCTSERVICES_H
