#ifndef IDARTSPOINTSETHINT_H
#define IDARTSPOINTSETHINT_H

#include "iplayerinput.h"
#include "idartsinputdb.h"

class IDartsPointSetHint
{
public:
    virtual void setDartsPointHint(const IPlayerInput* inputModel,const int& hint,IDartsInputDb* dbService) = 0;
};

#endif // IDARTSPOINTMODELSSERVICE_H
