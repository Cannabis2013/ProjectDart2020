#ifndef IDARTSPOINTSETHINT_H
#define IDARTSPOINTSETHINT_H

#include "iplayerinput.h"
#include "idbservice.h"

class IDartsPointSetHint
{
public:
    virtual void setDartsPointHint(const IModel<QUuid>* inputModel,const int& hint,IDbService* dbService) = 0;
};

#endif // IDARTSPOINTMODELSSERVICE_H
