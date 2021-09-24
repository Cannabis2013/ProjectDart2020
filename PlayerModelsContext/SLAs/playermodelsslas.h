#ifndef PLAYERMODELSSLAS_H
#define PLAYERMODELSSLAS_H

#include "PlayerModelsContext/SLAs/icreatejsonfromplayers.h"
#include "PlayerModelsContext/SLAs/icreateplayerfromjson.h"
#include "PlayerModelsContext/SLAs/igetplayerfromdb.h"
#include "PlayerModelsContext/SLAs/icreateplayermodels.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "ModelsContext/MCDbSLAs/iremovemodelsfromdb.h"

class PlayerModelsSLAs
{
public:
    ICreatePlayerFromJson *createPlayerModel() const;
    void setCreatePlayerModel(ICreatePlayerFromJson *newPlayerModelBuilder);
    ICreateJsonFromPlayers *dartsPlayerCreateJson() const;
    void setDartsPlayerJsonBuilder(ICreateJsonFromPlayers *newDartsPlayerJsonBuilder);
    IModelsDbContext *modelsDbContext() const;
    void setModelsDbContext(IModelsDbContext *newDartsPlayersDb);
    IGetPlayersFromDb *getPlayerModelsFromDb() const;
    void setGetPlayerModelsFromDb(IGetPlayersFromDb *newGetDartsPlayerModelsFromDb);
    ICreatePlayerModels *createPlayerModels() const;
    void setCreatePlayerModels(ICreatePlayerModels *newCreatePlayerModels);
    IRemoveModelsFromDb<IModelsDbContext> *removeFromDb() const;
    void setRemoveFromDb(IRemoveModelsFromDb<IModelsDbContext> *newRemoveFromDb);
private:
    ICreatePlayerFromJson *_createPlayerModel;
    ICreatePlayerModels *_createPlayerModels;
    IGetPlayersFromDb * _getPlayerModelsFromDb;
    ICreateJsonFromPlayers *_jsonBuilder;
    IModelsDbContext *_dbContext;
    IRemoveModelsFromDb<IModelsDbContext> *_removeFromDb;
};

#endif // PLAYERMODELSSERVICES_H
