#ifndef DARTSCREATETERMINALDIVISOR_H
#define DARTSCREATETERMINALDIVISOR_H

#include <idcmetainfo.h>
#include "idartsdivisorvalues.h"

class DartsCreateTerminalDivisor
{
public:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    DartsCreateTerminalDivisor(const IDartsDivisorValues *divisorValues)
    {
        _divisor = divisorValues->doubleDivisor();
    }
    int divisor() const
    {
        return _divisor;
    }
private:
    int _divisor;
};
#endif // DARTSGETTERMINALDIVISOR_H
