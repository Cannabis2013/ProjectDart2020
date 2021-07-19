#ifndef CREATEPLAYERMODELS_H
#define CREATEPLAYERMODELS_H

#include "icreateplayermodels.h"

class CreatePlayerModels : public ICreatePlayerModels
{
public:
    virtual QVector<const DartsModelsContext::IPlayerModel *> createPlayerModels(const QByteArray &json, const IDbGetIndexesUtility *getIndexes,
                                                                                 const IGetDartsPlayerModelsFromDb *getPlayerModels,
                                                                                 const IPlayerModelsDb *dbService) const override
    {
        auto playerIndexes = getIndexes->dbIndexesFromJson(json);
        auto playerModels = getPlayerModels->playerModels(playerIndexes,dbService);
        return playerModels;
    }
};

#endif // CREATEPLAYERMODELS_H
