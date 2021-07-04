#ifndef PLAYERMODELSLOCALJSONDB_H
#define PLAYERMODELSLOCALJSONDB_H

#include "playermodelsjsondb.h"
#include "createjsonfromplayermodels.h"
#include "createplayersfromjson.h"

class PlayerModelsLocalJsonDb : public DartsModelsContext::PlayerModelsJsonDb
{
public:
    PlayerModelsLocalJsonDb():
        DartsModelsContext::PlayerModelsJsonDb("Players")
    {
        using namespace DartsModelsContext;
        _createJsonFromModels = new CreateJsonFromPlayerModels;
        _createPlayerModels = new CreatePlayersFromJson;
        fetchModels();
    }
};

#endif // PLAYERMODELSLOCALJSONDB_H
