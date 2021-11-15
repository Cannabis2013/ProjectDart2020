#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H
#include "DartsModelsContext/TournamentsDbSLAs/igetdartstournament.h"
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
class GetDartsTournamentFromDb : public IGetDartsTournament
{
public:
    virtual IModel<QUuid> *get(const QUuid &tournamentId, const IModelsDbContext *dbService) const override
    {
        return dbService->model([tournamentId](IModel<QUuid> *m){
                if(m->id() == tournamentId)
                    return true;
                return false;
        });
    }
};

#endif // GETDARTSTOURNAMENTDATA_H
