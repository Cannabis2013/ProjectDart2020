#ifndef LOCALPLAYERSCONTEXT_H
#define LOCALPLAYERSCONTEXT_H

#include "PlayerModelsContext/playermodelscontext.h"
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "PlayerModelsContext/DbServices/playersdbcontext.h"
#include "FileOperationsContext/Services/readbytearray.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "PlayerModelsContext/Services/createjsonfromplayermodels.h"
#include "PlayerModelsContext/Services/createplayersfromjson.h"

class LocalPlayersContext : public PlayerModelsContext
{
public:
    LocalPlayersContext()
    {
        setServices();
        dbContext()->fetchModels(playerBuilder());
    }
private:
    void setServices()
    {
        setDbContext(new PlayersDbContext(new ReadByteArray(_dbFileName),new WriteByteArray(_dbFileName)));
        setGetPlayerModelsFromDb(new GetPlayersFromDb);
        setJsonBuilder(new CreateJsonFromPlayerModels);
        setPlayerBuilder(new CreatePlayersFromJson);
    }
    const QString _dbFileName = "PlayerModels";
};
#endif // LOCALPLAYERSCONTEXT_H
