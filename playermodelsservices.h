#ifndef PLAYERMODELSSERVICES_H
#define PLAYERMODELSSERVICES_H

#include <icreatejsonfromplayers.h>
#include <icreateplayerfromjson.h>
#include <igetplayerfromdb.h>
#include "icreateplayermodels.h"
#include "imodelsdbcontext.h"

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

private:
    ICreatePlayerFromJson *_createPlayerModel;
    ICreatePlayerModels *_createPlayerModels;
    IGetPlayersFromDb * _getPlayerModelsFromDb;
    ICreateJsonFromPlayers *_jsonBuilder;
    IModelsDbContext *_dbContext;
};

#endif // PLAYERMODELSSERVICES_H
