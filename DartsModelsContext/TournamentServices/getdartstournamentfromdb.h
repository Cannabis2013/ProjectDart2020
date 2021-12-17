#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H
#include "DartsModelsContext/TournamentsDbSLAs/igetdartstournament.h"
#include "DartsModelsContext/ModelSLAs/imodel.h"
#include "DartsModelsContext/TournamentModelsSLAs/idartstournament.h"
#include <quuid.h>
#include "DartsModelsContext/DbSLAs/idbcontext.h"
class GetDartsTournamentFromDb : public IGetDartsTournament<IModel<QUuid>,IDartsTournament>
{
public:
    virtual SuperModel *get(const QUuid &tournamentId, const IDbContext<BaseModel> *dbService) const override
    {
        auto model = dbService->model([tournamentId](BaseModel *m){
                if(m->id() == tournamentId)
                    return true;
                return false;
        });
        return dynamic_cast<SuperModel*>(model);
    }
};
#endif // GETDARTSTOURNAMENTDATA_H
