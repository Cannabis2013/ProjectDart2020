#ifndef IREMOVEDARTSINPUTSFROMDB_H
#define IREMOVEDARTSINPUTSFROMDB_H
#include "IDartsInputsDbContext.h"
class IRemoveDartsInputsFromDb
{
public:
    virtual IDartsInputsDbContext *removeInputsById(const QUuid &id, IDartsInputsDbContext *dbService) const = 0;
    virtual IDartsInputsDbContext *removeInputsByTournamentId(const QUuid &tournamentId, IDartsInputsDbContext *dbService) const= 0;
    virtual IDartsInputsDbContext *removeByTournamentIds(const QVector<QUuid> &tournamentIds, IDartsInputsDbContext *dbService) const = 0;
    virtual IDartsInputsDbContext *removeByHint(const QUuid &tournamentId, const int &hint, IDartsInputsDbContext *dbService) const = 0;
};


#endif // IREMOVEINPUTSFROMDB_H
