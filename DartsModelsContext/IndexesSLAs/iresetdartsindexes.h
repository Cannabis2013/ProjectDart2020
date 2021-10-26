#ifndef IRESETDARTSINDEXES_H
#define IRESETDARTSINDEXES_H
#include "ModelsContext/MCModelsSLAs/imodel.h"
#include <quuid.h>
#include "DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h"
class IResetDartsIndexes
{
public:
    virtual IDartsDbContext *reset(const QUuid &id, IDartsDbContext *dbContext) const = 0;
};
#endif // IRESETDARTSINDEXES_H
