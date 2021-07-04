#ifndef GETDATAFROMPLAYERMODELS_H
#define GETDATAFROMPLAYERMODELS_H

#include "igetdatafromplayermodels.h"
class GetDataFromPlayerModels : public IGetDataFromPlayerModels
{
public:
    virtual QVector<Id> createPlayerIds(const QVector<const Model *> &models) const override
    {
        QVector<Id> playerIds;
        for (const auto &model : models)
            playerIds << model->id();
        return playerIds;
    }
    virtual QVector<String> createPlayerNames(const QVector<const Model *> &models) const override
    {
        QVector<QString> playerNames;
        for (const auto &model : models)
            playerNames << model->playerName();
        return playerNames;
    }
};
#endif // DARTSPLAYERLISTSERVICE_H
