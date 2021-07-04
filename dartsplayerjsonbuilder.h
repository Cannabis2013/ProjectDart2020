#ifndef DARTSPLAYERJSONBUILDER_H
#define DARTSPLAYERJSONBUILDER_H

#include "idartsplayerjsonbuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DartsPlayerJsonBuilder : public IDartsPlayerJsonBuilder
{
    // ICreateJsonFromPlayerCredentials interface
public:
    virtual Json createJson(const QVector<Id> &playerIds, const QVector<String> &playerNames) const override
    {
        if(playerIds.count() != playerNames.count())
            return Json();
        QJsonArray arr;
        for (int i = 0, j = 0; i < playerIds.count() || j < playerNames.count(); ++i,++j) {
            QJsonObject obj;
            obj["playerId"] = playerIds.at(i).toString(QUuid::WithoutBraces);
            obj["playerName"] = playerNames.at(j);
            arr << obj;
        }
        return createByteArray(arr);

    }
    virtual Json createJson(const Id &playerId, const String &playerName) const override
    {
        QJsonObject obj;
        obj["playerId"] = playerId.toString(QUuid::WithoutBraces);
        obj["playerName"] = playerName;
        return createByteArray(obj);
    }

    virtual Json createJson(const QVector<const Player *> &playerModels) const override
    {
        QJsonArray arr;
        for (const auto &player : playerModels)
            arr << createJsonObjectFromPlayerModel(player);
        return createByteArray(arr);
    }

private:
    QJsonObject createJsonObjectFromPlayerModel(const Player *playerModel) const
    {
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
