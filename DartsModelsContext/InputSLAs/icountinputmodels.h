#ifndef ICOUNTINPUTMODELS_H
#define ICOUNTINPUTMODELS_H

#include <quuid.h>
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"

class ICountInputModels
{
public:
    virtual int count(const QUuid& tournamentId,const IModelsDbContext* service) const = 0;
};

#endif // IINPUTMODELSCOUNTSERVICE_H
