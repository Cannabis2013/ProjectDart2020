#ifndef DARTSCONSTRUCTSLAS_H
#define DARTSCONSTRUCTSLAS_H

#include "idartsthresholds.h"

class IDartsAttemptsService;
class IDartsModIdentifiers;
class IDartsterminalDivisor;
class IDartsDivisorValues;
class IDartsFieldValues;
class IDartsBoundaries;
class DartsConstructSLAs
{
public:
        IDartsBoundaries *boundaries() const {return _boundaries;}
        void setBoundariesService(IDartsBoundaries *service) {_boundaries = service;}
        IDartsFieldValues *fieldValues() const {return _fieldValues;}
        void setFieldValuesService(IDartsFieldValues *service) {_fieldValues = service;}
        IDartsDivisorValues *divisors() const {return _divisors;}
        void setDivisorsService(IDartsDivisorValues *service) {_divisors = service;}
        IDartsterminalDivisor *terminalDivisor() const {return _terminalDivisor;}
        void setTerminalDivisorService(IDartsterminalDivisor *service) {_terminalDivisor = service;}
        IDartsModIdentifiers *identifiers() const {return _identifiers;}
        void setIdentifiersService(IDartsModIdentifiers *service) {_identifiers = service;}
        IDartsAttemptsService *attemptsService() const {return _attempts;}
        void setAttemptsService(IDartsAttemptsService *service) {_attempts = service;}
        IDartsThresholds *thresholds() const {return _thresholds;}
        void setThresholds(IDartsThresholds *newThresholds) {_thresholds = newThresholds;}
private:
        IDartsBoundaries *_boundaries;
        IDartsThresholds *_thresholds;
        IDartsFieldValues *_fieldValues;
        IDartsDivisorValues *_divisors;
        IDartsterminalDivisor *_terminalDivisor;
        IDartsModIdentifiers *_identifiers;
        IDartsAttemptsService *_attempts;
};
#endif // DARTSCONSTRUCTSERVICES_H
