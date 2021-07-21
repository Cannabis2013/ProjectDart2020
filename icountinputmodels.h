#ifndef ICOUNTINPUTMODELS_H
#define ICOUNTINPUTMODELS_H

#include <quuid.h>
#include "idbservice.h"

class ICountInputModels
{
public:
    virtual int count(const QUuid& tournamentId,const IDbService* service) const = 0;
};

#endif // IINPUTMODELSCOUNTSERVICE_H
