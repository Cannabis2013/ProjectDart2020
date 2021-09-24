#ifndef CREATEJSONFROMPLAYERS_H
#define CREATEJSONFROMPLAYERS_H

#include "PlayerModelsContext/SLAs/icreatejsonfromplayers.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "PlayerModelsContext/SLAs/iplayermodel.h"

class CreateJsonFromPlayers : public ICreateJsonFromPlayers
{
    // ICreateJsonFromPlayerCredentials interface
public:
    virtual QByteArray createJson(const QVector<QUuid> &playerIds, const QVector<QString> &playerNames) const override
    {
        if(playerIds.count() != playerNames.count())
            return QByteArray();
        QJsonArray arr;
        for (int i = 0, j = 0; i < playerIds.count() || j < playerNames.count(); ++i,++j) {
            QJsonObject obj;
            obj["playerId"] = playerIds.at(i).toString(QUuid::WithoutBraces);
            obj["playerName"] = playerNames.at(j);
            arr << obj;
        }
        return createByteArray(arr);
    }

    virtual QByteArray createJson(const IModel<QUuid> *model) const override
    {
        QJsonObject obj = {{"winnerId",""},{"winnerId",""}};
        if(model != nullptr)
        {
            auto playerModel = dynamic_cast<const PlayersContext::IPlayerModel*>(model);
            auto winnerId = playerModel->id();
            auto playerName = playerModel->playerName();
            obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
            obj["winnerName"] = playerName;
        }
        return createByteArray(obj);
    }

    virtual QByteArray createJson(const QVector<const IModel<QUuid>*> &playerModels) const override
    {
        QJsonArray arr;
        for (const auto &player : playerModels)
            arr << createJsonObjectFromPlayerModel(player);
        return createByteArray(arr);
    }

private:
    QJsonObject createJsonObjectFromPlayerModel(const IModel<QUuid> *model) const
    {
        auto playerModel = dynamic_cast<const PlayersContext::IPlayerModel*>(model);
        QJsonObject obj;
        obj["playerId"] = playerModel->id().toString(QUuid::WithoutBraces);
        obj["playerName"] = playerModel->playerName();
        obj["playerMail"] = playerModel->email();
        return obj;
    }
    QByteArray createByteArray(const QJsonObject &obj) const
    {
        auto document = QJsonDocument(obj);
        auto json = document.toJson();
        return json;
    }
    QByteArray createByteArray(const QJsonArray &arr) const
    {
        auto document = QJsonDocument(arr);
        auto json = document.toJson();
        return json;
    }
};

#endif // CREATEJSONFROMDARTSPLAYERCREDENTIALS_H
