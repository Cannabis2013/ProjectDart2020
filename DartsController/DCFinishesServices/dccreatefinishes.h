#ifndef DCCREATEFINISHES_H
#define DCCREATEFINISHES_H

#include "dartscreatefinishes.h"
#include "dartsboundaries.h"
#include "dartsfieldvalues.h"
#include "dartsthreshold.h"
#include "dartscreateterminalthreshold.h"
#include "dartsdivisors.h"
#include "dartsterminaldivisor.h"
#include "dartsmodidentifiers.h"
#include "dartsdefaultattempts.h"

class DCCreateFinishes : public DartsCreateFinishes
{
public:
    static DCCreateFinishes *createInstance()
    {
        return new DCCreateFinishes();
    }
private:
    DCCreateFinishes()
    {
        setBoundariesService(new DartsBoundaries);
        setFieldValuesService(new DartsFieldValues);
        setDivisorsService(new DartsDivisors);
        setThresholdsService(new DartsThresholds(DartsCreateTerminalThreshold(new DartsBoundaries)));
        setTerminalDivisorService(new DartsTerminalDivisor);
        setIdentifiersService(new DartsModIdentifiers);
        setAttemptsService(new DartsDefaultAttempts);
    }
};
#endif // DPCCONSTRUCTROW_H
