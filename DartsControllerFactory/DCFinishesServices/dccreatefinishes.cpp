#include "dccreatefinishes.h"
#include "defaultthresholds.h"
#include "dartsboundaries.h"
#include "dartsfieldvalues.h"
#include "dartsdivisors.h"
#include "dartsterminaldivisor.h"
#include "dartsmodidentifiers.h"
#include "dartsdefaultattempts.h"
DCCreateFinishes::DCCreateFinishes()
{
    setBoundariesService(new DartsBoundaries);
    setFieldValuesService(new DartsFieldValues);
    setDivisorsService(new DartsDivisors);
    setTerminalDivisorService(new DartsTerminalDivisor);
    setIdentifiersService(new DartsModIdentifiers);
    setAttemptsService(new DartsDefaultAttempts);
    setThresholds(new DefaultThresholds);
}
