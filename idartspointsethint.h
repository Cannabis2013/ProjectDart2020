#ifndef IDARTSPOINTSETHINT_H
#define IDARTSPOINTSETHINT_H

#include "iplayerinput.h"
#include "imodelsdbcontext.h"

class IDartsPointSetHint
{
public:
    virtual void setDartsPointHint(const IModel<QUuid>* inputModel,const int& hint,IModelsDbContext* dbService) = 0;
};

#endif // IDARTSPOINTMODELSSERVICE_H
