#ifndef DETERMINECONTROLLERSTATEBYWINNERID_H
#define DETERMINECONTROLLERSTATEBYWINNERID_H

#include "iunaryservice.h"
#include <quuid.h>

namespace DartsControllerContext {
    class DetermineControllerStateByWinnerId : public
            IUnaryService<const QUuid&,int>
    {
    public:
        enum ControllerState {
            GameBusy = 0x11, // Game is idle but in progress
            Stopped = 0x12, // Game is stopped and no longer accepts input
            AwaitsInput = 0x13, // This should indicate that the gamecontroller is in a state where it awaits new player input
            WinnerDeclared = 0x15,
            NotInitialized = 0x16, // Controller is not initialized with tournament and, if necessary, appropriate indexes
            Initialized = 0x17,
            UndoState = 0x1F,
            RedoState = 0x20,
            AddScoreState = 0x21,
            UpdateContextState = 0x22,
            resetState = 0x29,
            idle = 0xA
        };
        int service(const QUuid& winnerId) override
        {
            if(winnerId == QUuid())
                return Initialized;
            else
                return WinnerDeclared;
        }
    };
}

#endif // DETERMINECONTROLLERSTATEBYWINNERID_H
