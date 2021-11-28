#ifndef IGETDARTSTOURNAMENT_H
#define IGETDARTSTOURNAMENT_H
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h"
template<typename TBaseModel, typename TSuperModel = TBaseModel>
class IGetDartsTournament
{
public:
    typedef TBaseModel BaseModel;
    typedef TSuperModel SuperModel;
    virtual SuperModel *get(const QUuid &tournamentId, const IDbContext<BaseModel> *dbService) const = 0;
};

#endif // IGETDARTSTOURNAMENTDATA_H
