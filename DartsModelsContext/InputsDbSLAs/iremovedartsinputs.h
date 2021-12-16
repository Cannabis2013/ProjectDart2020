#ifndef IREMOVEDARTSINPUTS_H
#define IREMOVEDARTSINPUTS_H
#include "DartsModelsContext/DbSLAs/idbcontext.h"
template<typename TDbModel, typename TUuid, typename TDbCtx>
class IRemoveDartsInputs
{
public:
    typedef TDbModel Model;
    typedef TDbCtx DbCtx;
    typedef TUuid Uuid;
    virtual IDbContext<Model> *removeInputsById(const Uuid &id, DbCtx *dbService) const = 0;
    virtual IDbContext<Model> *removeInputsByTournamentId(const Uuid &tournamentId, DbCtx *dbService) const= 0;
    virtual IDbContext<Model> *removeByTournamentIds(const QVector<Uuid> &tournamentIds, DbCtx *dbService) const = 0;
    virtual IDbContext<Model> *removeByHint(const Uuid &tournamentId, const int &hint, DbCtx *dbService) const = 0;
};
#endif // IREMOVEINPUTSFROMDB_H
