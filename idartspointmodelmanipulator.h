#ifndef IDARTSPOINTMODELMANIPULATOR_H
#define IDARTSPOINTMODELMANIPULATOR_H

#include "iplayerinput.h"
#include "idartsinputdb.h"

namespace DartsModelsContext {
    class IDartsPointModelManipulator
    {
    public:
        virtual void setDartsPointHint(const IPlayerInput* inputModel,const int& hint,IDartsInputDb* dbService) = 0;
    };
}

#endif // IDARTSPOINTMODELSSERVICE_H
