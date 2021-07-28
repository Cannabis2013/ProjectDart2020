#ifndef CREATEPLAYERMODELS_H
#define CREATEPLAYERMODELS_H

#include "icreateplayermodels.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class CreatePlayerModels : public ICreatePlayerModels
{
public:
    virtual QVector<const IModel<QUuid> *> createPlayerModels(const QByteArray &json,
                                                              const IGetPlayersFromDb *getPlayerModels,
                                                              const IModelsDbContext *dbService) const override
    {
        auto playerIndexes = createIndexesFromJson(json);
        auto playerModels = getPlayerModels->models(playerIndexes,dbService);
        return playerModels;
    }
private:
    QVector<int> createIndexesFromJson(const QByteArray &json) const
    {
        auto obj = createJsonObject(json);
        auto jsonValue = obj.value("indexes");
        auto arr = jsonValue.toArray();
        auto indexes = createIndexesFromArray(arr);
        return indexes;
    }
    QJsonObject createJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        auto obj = document.object();
        return obj;
    }
    QVector<int> createIndexesFromArray(const QJsonArray &arr) const
    {
        QVector<int> indexes;
        for (const auto &jsonValue : arr)
            indexes << jsonValue.toInt();
        return indexes;
    }
};

#endif // CREATEPLAYERMODELS_H
