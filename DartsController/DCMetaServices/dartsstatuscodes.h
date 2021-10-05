#ifndef DARTSSTATUSCODES_H
#define DARTSSTATUSCODES_H

#include "DartsController/DCMetaSLAs/idartsstatuscodes.h"
class DCStatusCodes : public IDartsStatusCodes
{
public:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    virtual int initialized() const override
    {
        return Initialized;
    }
    virtual int running() const override
    {
        return Running;
    }
    virtual int winnerFound() const override
    {
        return WinnerDeclared;
    }
    virtual int awaitsInput() const override
    {
        return AwaitsInput;
    }
};
#endif // DARTSSTATUSCODES_H
