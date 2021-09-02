#ifndef DETERMINECONTROLLERSTATEBYWINNERID_H
#define DETERMINECONTROLLERSTATEBYWINNERID_H

#include "iunaryservice.h"
#include <quuid.h>

class DetermineControllerStateByWinnerId : public IUnaryService<const QUuid&,int>
{
public:
    enum ControllerState {
        WinnerDeclared = 0x15, // Controller is not initialized with tournament and, if necessary, appropriate indexes
        Initialized = 0x17,
    };
    int service(const QUuid& winnerId) override
    {
        if(winnerId == QUuid())
            return Initialized;
        else
            return WinnerDeclared;
    }
};
#endif // DETERMINECONTROLLERSTATEBYWINNERID_H
