#ifndef DARTSSTATUSCODES_H
#define DARTSSTATUSCODES_H

#include "DartsMetaCollection/idartsstatuscodes.h"
class DCStatusCodes : public IDartsStatusCodes
{
public:
    enum ControllerState {
        Initialized = 0x0,
        Running = 0x2,
        WinnerDeclared = 0x4
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
};
#endif // DARTSSTATUSCODES_H
