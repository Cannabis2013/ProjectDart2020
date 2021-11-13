#ifndef IUPDATEDARTSINDEXES_H
#define IUPDATEDARTSINDEXES_H
#include "DartsModelsContext/TournamentsDbSLAs/IDartsDbContext.h"
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
class IUpdateDartsIndexes
{
public:
    virtual IDartsDbContext *update(IDartsIndex *model, const QUuid &tournament, IDartsDbContext *dbContext) const = 0;
};
#endif // IUPDATEDARTSINDEXES_H
