#ifndef PLAYERMODELSLOCALJSONDB_H
#define PLAYERMODELSLOCALJSONDB_H

#include "playermodelsjsondb.h"
#include "createjsonfromplayermodels.h"
#include "createplayersfromjson.h"

class PlayerModelsLocalJsonDb : public ModelsContext::PlayerModelsJsonDb
{
public:
    PlayerModelsLocalJsonDb():
        ModelsContext::PlayerModelsJsonDb("Players")
    {
        using namespace ModelsContext;
        _createJsonFromModels = new CreateJsonFromPlayerModels;
        _createPlayerModels = new CreatePlayersFromJson;
        fetchModels();
    }
};

#endif // PLAYERMODELSLOCALJSONDB_H
