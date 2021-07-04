#ifndef DARTSTOURNAMENTSJSONDB_H
#define DARTSTOURNAMENTSJSONDB_H

#include "tournamentsjsondb.h"
#include "createjsonfromdartstournaments.h"
#include "createdartstournamentsfromjson.h"
class DartsTournamentsJsonDb : public TournamentsJsonDb
{
public:
    DartsTournamentsJsonDb():
        TournamentsJsonDb("DartsTournaments")
    {
        _createJsonFromModels = new CreateJsonFromDartsTournaments;
        _createModelsFromJson = new CreateDartsTournamentsFromJson;
        fetchModels();
    }
};

#endif // DARTSTOURNAMENTSJSONDB_H
