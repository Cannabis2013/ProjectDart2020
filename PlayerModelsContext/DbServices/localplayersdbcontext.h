#ifndef LOCALPLAYERSDBCONTEXT_H
#define LOCALPLAYERSDBCONTEXT_H

#include "jsonplayersdbcontext.h"
#include "PlayerModelsContext/SLAs/createjsonfromplayermodels.h"
#include "createplayersfromjson.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "FileOperationsContext/Services/readbytearray.h"

class LocalPlayersDbContext : public PlayersContext::JsonPlayersDbContext
{
public:
    LocalPlayersDbContext()
    {
        setServices();
        fetchModels();
    }
private:
    void setServices()
    {
        setCreateJsonFromModels(new PlayersContext::CreateJsonFromPlayerModels);
        setCreateModelsFromJson(new CreatePlayersFromJson);
        setWriteJsonToFile(new WriteByteArray(_fileName));
        setReadJsonFromFile(new ReadByteArray(_fileName));
    }
    const QString _fileName = "PlayerModels";
};

#endif // PLAYERMODELSLOCALJSONDB_H
