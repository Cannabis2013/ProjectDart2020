#ifndef DARTSCONSTRUCTSLAS_H
#define DARTSCONSTRUCTSLAS_H
#include "DartsController/DCFinishesSLAs/idartsfieldvalues.h"
#include "DartsController/DCFinishesSLAs/idartsthresholdvalues.h"
#include "DartsController/DCFinishesSLAs/idartsboundaries.h"
#include "DartsController/DCFinishesSLAs/idartsdivisorvalues.h"
#include "DartsController/DCFinishesSLAs/idartsterminaldivisor.h"
#include "DartsController/DCFinishesSLAs/idartsmodidentifiers.h"
#include "DartsController/DCFinishesSLAs/idartsattemptsservice.h"
class DartsConstructSLAs
{
public:
    IDartsBoundaries *boundaries() const
    {
        return _boundaries;
    }
    void setBoundariesService(IDartsBoundaries *service)
    {
        _boundaries = service;
    }

    IDartsFieldValues *fieldValues() const
    {
        return _fieldValues;
    }
    void setFieldValuesService(IDartsFieldValues *service)
    {
        _fieldValues = service;
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
    void setTerminalDivisorService(IDartsterminalDivisor *service)
    {
        _terminalDivisor = service;
    }
    IDartsModIdentifiers *identifiers() const
    {
        return _identifiers;
    }
    void setIdentifiersService(IDartsModIdentifiers *service)
    {
        _identifiers = service;
    }
    IDartsAttemptsService *attemptsService() const
    {
        return _attempts;
    }
    void setAttemptsService(IDartsAttemptsService *service)
    {
        _attempts = service;
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
