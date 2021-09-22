#ifndef PLAYERMODELSSERVICES_H
#define PLAYERMODELSSERVICES_H

#include <icreatejsonfromplayers.h>
#include <icreateplayerfromjson.h>
#include <igetplayerfromdb.h>
#include "icreateplayermodels.h"
#include "ModelsContext/imodelsdbcontext.h"
#include "ModelsContext/iremovemodelsfromdb.h"

class PlayerModelsServices
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
