#ifndef IUPDATEDARTSINDEXES_H
#define IUPDATEDARTSINDEXES_H

#include "DartsModelsContext/IndexesDbSLAs/idartsindexesdbcontext.h"

class IUpdateDartsIndexes
{
public:
    virtual IDartsIndexesDbContext *update(IModel<QUuid> *model, IDartsIndexesDbContext *dbContext) const = 0;
};
#endif // IUPDATEDARTSINDEXES_H
