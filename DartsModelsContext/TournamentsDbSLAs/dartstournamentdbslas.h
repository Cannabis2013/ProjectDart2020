#ifndef DARTSTOURNAMENTDBJSONSLAS_H
#define DARTSTOURNAMENTDBJSONSLAS_H

#include "DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartstournamentbuilder.h"
#include "IDartsDbContext.h"
#include "igetdartstournamentfromdb.h"

class DartsTournamentDbSLAs
{
public:
    IDartsTournamentBuilder *tournamentBuilder() const
    {
        return _tournamentBuilder;
    }
    void setTournamentBuilder(IDartsTournamentBuilder *service)
    {
        _tournamentBuilder = service;
    }
    ITournamentJsonBuilder *tournamentJsonBuilder() const
    {
        return _tournamentJsonBuilder;
    }
    void setTournamentJsonBuilder(ITournamentJsonBuilder *service)
    {
        _tournamentJsonBuilder = service;
    }
    IDartsDbContext *tournamentsDbContext() const
    {
        return _dartsTournamentsDb;
    }
    void setTournamentsDbContext(IDartsDbContext *service)
    {
        _dartsTournamentsDb = service;
    }
    IGetDartsTournamentFromDb *getTournament() const
    {
        return _getTournament;
    }
    void setGetTournament(IGetDartsTournamentFromDb *service)
    {
        _getTournament = service;
    }
private:
    IGetDartsTournamentFromDb *_getTournament;
    IDartsDbContext *_dartsTournamentsDb;
    IDartsTournamentBuilder *_tournamentBuilder;
    ITournamentJsonBuilder *_tournamentJsonBuilder;
};
#endif // MODELSDBJSONSLAS_H
