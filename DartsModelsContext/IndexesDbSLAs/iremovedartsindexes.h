#ifndef IREMOVEDARTSINDEXES_H
#define IREMOVEDARTSINDEXES_H

#include "idartsindexesdbcontext.h"

class IRemoveDartsIndexes
{
public:
    virtual IDartsIndexesDbContext *removeByTournamentIds(const QVector<QUuid> &tournamentIds, IDartsIndexesDbContext *dbContext) const = 0;
};
#endif // IREMOVEDARTSINDEXES_H
