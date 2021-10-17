#ifndef IRESETDARTSINDEXES_H
#define IRESETDARTSINDEXES_H

#include <quuid.h>
#include "DartsModelsContext/IndexesDbSLAs/idartsindexesdbcontext.h"

class IResetDartsIndexes
{
public:
    virtual IDartsIndexesDbContext *reset(const QUuid &tournamentId, const IDartsIndexesBuilder *builderContext,
                                          IDartsIndexesDbContext *dbContext) const = 0;
};
#endif // IRESETDARTSINDEXES_H
