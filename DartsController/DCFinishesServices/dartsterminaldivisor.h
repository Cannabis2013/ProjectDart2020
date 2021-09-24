#ifndef DARTSTERMINALDIVISOR_H
#define DARTSTERMINALDIVISOR_H

#include "DartsController/DCFinishesSLAs/idartsterminaldivisor.h"
class DartsTerminalDivisor : public IDartsterminalDivisor
{
public:
    virtual int divisor() const override
    {
        return _terminalDivisor;
    }
private:
    const int _terminalDivisor = 2;
};
#endif // DARTSTERMINALDIVISOR_H
