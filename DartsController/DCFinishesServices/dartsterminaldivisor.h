#ifndef DARTSTERMINALDIVISOR_H
#define DARTSTERMINALDIVISOR_H

#include "DartsController/DCFinishesSLAs/idartsterminaldivisor.h"
#include "dartscreateterminaldivisor.h"
class DartsTerminalDivisor : public IDartsterminalDivisor
{
public:
    DartsTerminalDivisor(DartsCreateTerminalDivisor createDivisor):
        _terminalDivisor(createDivisor.divisor())
    {}
    virtual int divisor() const override
    {
        return _terminalDivisor;
    }
private:
    const int _terminalDivisor;
};
#endif // DARTSTERMINALDIVISOR_H
