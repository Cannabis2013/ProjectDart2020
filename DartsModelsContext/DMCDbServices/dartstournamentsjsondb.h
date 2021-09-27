#ifndef DARTSTOURNAMENTSJSONDB_H
#define DARTSTOURNAMENTSJSONDB_H

#include "DartTournamentsContext/DTCDbServices/tournamentsjsondb.h"
#include "DartsModelsContext/DMCTournamentServices/createjsonfromdartstournaments.h"
#include "DartsModelsContext/DMCTournamentServices/createdartstournamentsfromjson.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "FileOperationsContext/Services/readbytearray.h"
class DartsTournamentsJsonDb : public TournamentsJsonDb
{
public:
    DartsTournamentsJsonDb():
        TournamentsJsonDb("DartsTournamentModels")
    {
        setServices();
        fetchModels();
    }
private:
    void setServices()
    {
        setCreateJsonFromModels(new CreateJsonFromDartsTournaments);
        setCreateModelsFromJson(new CreateDartsTournamentsFromJson);
        setWriteJsonToFile(new WriteByteArray(_fileName));
        setReadJsonFromFile(new ReadByteArray(_fileName));
    }
};

#endif // DARTSTOURNAMENTSJSONDB_H
