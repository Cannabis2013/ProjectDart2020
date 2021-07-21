#ifndef PLAYERMODELSSERVICES_H
#define PLAYERMODELSSERVICES_H

#include <idartsplayerjsonbuilder.h>
#include <idartsplayermodelbuilder.h>
#include <igetdartsplayermodelsfromdb.h>
#include <igetdatafromplayermodels.h>
#include "icreateplayermodels.h"
#include "idbservice.h"

class PlayerModelsServices
{
public:
    IDartsPlayerModelBuilder *createPlayerModel() const;
    void setCreatePlayerModel(IDartsPlayerModelBuilder *newPlayerModelBuilder);
    IGetDataFromPlayerModels *getDataFromPlayerModels() const;
    void setGetDataFromPlayerModels(IGetDataFromPlayerModels *newGetDataFromPlayerModels);
    IDartsPlayerJsonBuilder *dartsPlayerCreateJson() const;
    void setDartsPlayerJsonBuilder(IDartsPlayerJsonBuilder *newDartsPlayerJsonBuilder);
    IDbService *dartsPlayersDb() const;
    void setDartsPlayersDb(IDbService *newDartsPlayersDb);
    IGetDartsPlayerModelsFromDb *getPlayerModelsFromDb() const;
    void setGetPlayerModelsFromDb(IGetDartsPlayerModelsFromDb *newGetDartsPlayerModelsFromDb);
    ICreatePlayerModels *createPlayerModels() const;
    void setCreatePlayerModels(ICreatePlayerModels *newCreatePlayerModels);

private:
    IDartsPlayerModelBuilder *_createPlayerModel;
    ICreatePlayerModels *_createPlayerModels;
    IGetDataFromPlayerModels *_getDataFromPlayerModels;
    IGetDartsPlayerModelsFromDb * _getPlayerModelsFromDb;
    IDartsPlayerJsonBuilder *_dartsPlayerJsonBuilder;
    IDbService *_dartsPlayersDb;
};

#endif // PLAYERMODELSSERVICES_H
