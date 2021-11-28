#ifndef IREMOVEDARTSINPUTS_H
#define IREMOVEDARTSINPUTS_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include "ModelsContext/DbSLAs/idbcontext.h"
template<typename TDbModel, typename TUuid>
class IRemoveDartsInputs
{
public:
    typedef TDbModel Model;
    typedef TUuid Uuid;
    virtual IDbContext<Model> *removeInputsById(const Uuid &id, IDbContext<Model> *dbService) const = 0;
    virtual IDbContext<Model> *removeInputsByTournamentId(const Uuid &tournamentId, IDbContext<Model> *dbService) const= 0;
    virtual IDbContext<Model> *removeByTournamentIds(const QVector<Uuid> &tournamentIds, IDbContext<Model> *dbService) const = 0;
    virtual IDbContext<Model> *removeByHint(const Uuid &tournamentId, const int &hint, IDbContext<Model> *dbService) const = 0;
};


#endif // IREMOVEINPUTSFROMDB_H
