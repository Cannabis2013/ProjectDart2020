#ifndef ICOUNTINPUTMODELS_H
#define ICOUNTINPUTMODELS_H

#include <quuid.h>
#include "ModelsContext/imodelsdbcontext.h"

class ICountInputModels
{
public:
    virtual int count(const QUuid& tournamentId,const IModelsDbContext* service) const = 0;
};

#endif // IINPUTMODELSCOUNTSERVICE_H
