#ifndef DARTSTOURNAMENTDBJSONSLAS_H
#define DARTSTOURNAMENTDBJSONSLAS_H

#include "DartsModelsContext/TournamentsDbSLAs/itournamentjsonbuilder.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h"
#include "IDartsDbContext.h"
#include "igetdartstournament.h"

class DartsTournamentDbSLAs
{
public:
    IDartsBuilder *tournamentBuilder() const
    {
        return _tournamentBuilder;
    }
    void setTournamentBuilder(IDartsBuilder *service)
    {
        _tournamentBuilder = service;
    }
    IDartsJsonBuilder *tournamentJsonBuilder() const
    {
        return _tournamentJsonBuilder;
    }
    void setTournamentJsonBuilder(IDartsJsonBuilder *service)
    {
        _tournamentJsonBuilder = service;
    }
    IDartsDbContext *dartsDbContext() const
    {
        return _dartsDb;
    }
    void setDartsDbContext(IDartsDbContext *service)
    {
        _dartsDb = service;
    }
    IGetDartsTournament *getTournament() const
    {
        return _getTournament;
    }
    void setGetTournament(IGetDartsTournament *service)
    {
        _getTournament = service;
    }
private:
    IGetDartsTournament *_getTournament;
    IDartsDbContext *_dartsDb;
    IDartsBuilder *_tournamentBuilder;
    IDartsJsonBuilder *_tournamentJsonBuilder;
};
#endif // MODELSDBJSONSLAS_H
