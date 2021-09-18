#ifndef IDARTSINPUTSETHINT_H
#define IDARTSINPUTSETHINT_H

#include "iplayerinput.h"
#include "imodelsdbcontext.h"

class IDartsInputSetHint
{
public:
    virtual void setHint(const IModel<QUuid>* inputModel,const int& hint,IModelsDbContext* dbService) = 0;
};

#endif // IDARTSPOINTMODELSSERVICE_H
