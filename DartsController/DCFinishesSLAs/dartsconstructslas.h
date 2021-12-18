#ifndef DARTSCONSTRUCTSLAS_H
#define DARTSCONSTRUCTSLAS_H
#include "DCFinishesSLAs/idartsfieldvalues.h"
#include "DCFinishesSLAs/idartsthresholdvalues.h"
#include "DCFinishesSLAs/idartsboundaries.h"
#include "DCFinishesSLAs/idartsdivisorvalues.h"
#include "DCFinishesSLAs/idartsterminaldivisor.h"
#include "DCFinishesSLAs/idartsmodidentifiers.h"
#include "DCFinishesSLAs/idartsattemptsservice.h"
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
