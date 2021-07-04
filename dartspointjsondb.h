#ifndef DARTSPOINTJSONDB_H
#define DARTSPOINTJSONDB_H

#include "dartsinputjsondb.h"
#include "createdartspointsfromjson.h"
#include "createjsonfromdartspoints.h"


namespace DartsModelsContext
{
    class DartsPointJsonDb : public DartsInputJsonDb
    {
    public:
        DartsPointJsonDb():
            DartsInputJsonDb("DartsPointModels")
        {
            _createInputModelsFromJson = new CreateDartsPointsFromJson;
            _createJsonFromInputModels = new CreateJsonFromDartsPoints;
            fetchModels();
        }
    };
}


#endif // DARTSPOINTDBSERVICE_H
