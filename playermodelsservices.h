#ifndef PLAYERMODELSSERVICES_H
#define PLAYERMODELSSERVICES_H

#include <idartsplayerdbmanipulator.h>
#include <idartsplayerjsonbuilder.h>
#include <idartsplayermodelbuilder.h>
#include <igetdartsplayermodelsfromdb.h>
#include <igetdatafromplayermodels.h>
#include "icreateplayermodels.h"

class PlayerModelsServices
{
public:
    IDartsPlayerModelBuilder *createPlayerModel() const;
    void setCreatePlayerModel(IDartsPlayerModelBuilder *newPlayerModelBuilder);
    IGetDataFromPlayerModels *getDataFromPlayerModels() const;
    void setGetDataFromPlayerModels(IGetDataFromPlayerModels *newGetDataFromPlayerModels);
    IDartsPlayerJsonBuilder *dartsPlayerCreateJson() const;
    void setDartsPlayerJsonBuilder(IDartsPlayerJsonBuilder *newDartsPlayerJsonBuilder);
    IDartsPlayerDbManipulator *playerDbManipulator() const;
    void setPlayerDbManipulator(IDartsPlayerDbManipulator *newPlayerDbManipulator);
    IPlayerModelsDb *dartsPlayersDb() const;
    void setDartsPlayersDb(IPlayerModelsDb *newDartsPlayersDb);
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
    IDartsPlayerDbManipulator *_playerDbManipulator;
    IPlayerModelsDb *_dartsPlayersDb;
};

#endif // PLAYERMODELSSERVICES_H
