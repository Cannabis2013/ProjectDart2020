#ifndef DARTSPOINTJSONDB_H
#define DARTSPOINTJSONDB_H

#include "dartsinputjsondb.h"
#include "createdartspointsfromjson.h"
#include "dartsdbcreatejsonfrompoints.h"


namespace DartsDbContext
{
    class DartsPointJsonDb : public DartsInputJsonDb
    {
    public:
        DartsPointJsonDb():
            DartsInputJsonDb("DartsPointModels")
        {
            _createInputModelsFromJson = new CreateDartsPointsFromJson;
            _createJsonFromInputModels = new DartsDbCreatejsonFromPoints;
            fetchModels();
        }
    };
}


#endif // DARTSPOINTDBSERVICE_H
