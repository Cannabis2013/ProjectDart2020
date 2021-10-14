#ifndef IGETDARTSINDEXESMODEL_H
#define IGETDARTSINDEXESMODEL_H

#include <quuid.h>
#include <ModelsContext/MCDbSLAs/imodelsdbcontext.h>
#include "ModelsContext/MCModelsSLAs/imodel.h"

class IGetDartsIndexesModel
{
public:
    virtual IModel<QUuid> *indexesModel(const QUuid &tournamentId, const IModelsDbContext *dbContext) const = 0;
};

#endif // IGETDARTSINDEXES_H
