#ifndef PLAYERMODELSSERVICES_H
#define PLAYERMODELSSERVICES_H

#include <idartsplayerdbmanipulator.h>
#include <idartsplayerjsonbuilder.h>
#include <idartsplayermodelbuilder.h>
#include <igetdartsplayermodelsfromdb.h>
#include <igetdatafromplayermodels.h>


class PlayerModelsServices
{
public:
    IDartsPlayerModelBuilder *playerModelBuilder() const;
    void setPlayerModelBuilder(IDartsPlayerModelBuilder *newPlayerModelBuilder);
    IGetDataFromPlayerModels *getDataFromPlayerModels() const;
    void setGetDataFromPlayerModels(IGetDataFromPlayerModels *newGetDataFromPlayerModels);
    IDartsPlayerJsonBuilder *dartsPlayerJsonBuilder() const;
    void setDartsPlayerJsonBuilder(IDartsPlayerJsonBuilder *newDartsPlayerJsonBuilder);
    IDartsPlayerDbManipulator *playerDbManipulator() const;
    void setPlayerDbManipulator(IDartsPlayerDbManipulator *newPlayerDbManipulator);
    IPlayerModelsDb *dartsPlayersDb() const;
    void setDartsPlayersDb(IPlayerModelsDb *newDartsPlayersDb);
    IGetDartsPlayerModelsFromDb *getPlayerModelsFromDb() const;
    void setGetPlayerModelsFromDb(IGetDartsPlayerModelsFromDb *newGetDartsPlayerModelsFromDb);

private:
    IDartsPlayerModelBuilder *_playerModelBuilder;
    IGetDataFromPlayerModels *_getDataFromPlayerModels;
    IGetDartsPlayerModelsFromDb * _getPlayerModelsFromDb;
    IDartsPlayerJsonBuilder *_dartsPlayerJsonBuilder;
    IDartsPlayerDbManipulator *_playerDbManipulator;
    IPlayerModelsDb *_dartsPlayersDb;
};

#endif // PLAYERMODELSSERVICES_H
