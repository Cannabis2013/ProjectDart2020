#ifndef DARTSSCOREJSONDB_H
#define DARTSSCOREJSONDB_H

#include "dartsinputjsondb.h"
#include "createjsonfromdartsscoremodels.h"
#include "createdartsscoremodelsfromjson.h"

namespace DartsModelsContext {
    class DartsScoreJsonDb : public DartsInputJsonDb
    {
    public:
        DartsScoreJsonDb():
            DartsInputJsonDb("DartsScoreModels")
        {
            _createJsonFromInputModels = new CreateJsonFromDartsScoreModels;
            _createInputModelsFromJson = new CreateDartsScoreModelsFromjson;
            fetchModels();
        }
    };
}

#endif // DARTSSSCOREJSONDB_H
