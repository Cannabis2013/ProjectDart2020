#ifndef DARTSTOURNAMENTSJSONDB_H
#define DARTSTOURNAMENTSJSONDB_H

#include "tournamentsjsondb.h"
#include "createjsonfromdartstournaments.h"
#include "createdartstournamentsfromjson.h"
#include "writebytearray.h"
#include "readbytearray.h"
class DartsTournamentsJsonDb : public TournamentsJsonDb
{
public:
    DartsTournamentsJsonDb()
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
    const QString _fileName = "DartsTournamentModels";
};

#endif // DARTSTOURNAMENTSJSONDB_H
