#include "dccreatefinishes.h"

DCCreateFinishes::DCCreateFinishes()
{
    setBoundariesService(new DartsBoundaries);
    setFieldValuesService(new DartsFieldValues);
    setDivisorsService(new DartsDivisors);
    setTerminalDivisorService(new DartsTerminalDivisor);
    setIdentifiersService(new DartsModIdentifiers);
    setAttemptsService(new DartsDefaultAttempts);
}
