#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H
#include "TournamentsDbSLAs/igetdartstournament.h"
#include "ModelSLAs/imodel.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include <quuid.h>
#include "DbSLAs/idbcontext.h"
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
