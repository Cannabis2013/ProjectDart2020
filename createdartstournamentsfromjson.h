#ifndef CREATEDARTSTOURNAMENTSFROMJSON_H
#define CREATEDARTSTOURNAMENTSFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "dartstournament.h"
#include "icreatedartstournamentsfromjson.h"

class CreateDartsTournamentsFromJson :
        public ICreateDartsTournamentModelsFromJson
{
public:
    virtual QVector<const ITournament *> create(const QByteArray &json) const override
    {
        auto obj = createJsonobject(json);
        return createModels(obj);
    }
private:
    QJsonObject createJsonobject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();;
    }
    QVector<const ITournament *> createModels(const QJsonObject &obj) const
    {
        auto arr = createJsonArray(obj);
        return createModels(arr);
    }
    const QVector<const ITournament*> createModels(const QJsonArray &arr) const
    {
        QVector<const ITournament*> list;
        for (const auto& jsonValue : arr)
            list << createModel(jsonValue);
        return list;
    }
    const QJsonArray createJsonArray(const QJsonObject &obj) const
    {
        auto arr = obj.value("DartsTournaments").toArray();
        return arr;
    }
    const IDartsTournament* createModel(const QJsonValue& jsonValue) const
    {
        using namespace DartsModelsContext;
        auto jsonObject = jsonValue.toObject();
        auto dartsTournamentModel = DartsTournament::createInstance();
        dartsTournamentModel->setId(QUuid(jsonObject.value("id").toString()));
        dartsTournamentModel->setTitle(jsonObject.value("title").toString());
        dartsTournamentModel->setGameMode(jsonObject.value("gameMode").toInt());
        dartsTournamentModel->setKeyPoint(jsonObject.value("keyPoint").toInt());
        dartsTournamentModel->setAttempts(jsonObject.value("attempts").toInt());
        dartsTournamentModel->setTerminalKeyCode(jsonObject.value("terminalKeyCode").toInt());
        dartsTournamentModel->setDisplayHint(jsonObject.value("displayHint").toInt());
        dartsTournamentModel->setInputMode(jsonObject.value("inputHint").toInt());
        dartsTournamentModel->setStatus(jsonObject.value("status").toInt());
        dartsTournamentModel->setWinnerId(QUuid(jsonObject.value("winnerId").toString("")));
        auto arr1 = jsonObject.value("assignedPlayerIds").toArray();
        auto assignedPlayerIds = buildPlayerIdsByJsonArray(arr1);
        dartsTournamentModel->setAssignedPlayerIdentities(assignedPlayerIds);
        auto arr2 = jsonObject.value("assignedPlayerNames").toArray();
        auto playerNames = createPlayerNamesFromJsonArray(arr2);
        dartsTournamentModel->setAssignedPlayerNames(playerNames);
        return dartsTournamentModel;
    }
    QVector<QUuid> buildPlayerIdsByJsonArray(const QJsonArray& arr) const
    {
        QVector<QUuid> assignedPlayerIds;
        for (const auto& jsonValue : arr) {
            auto stringId = jsonValue.toString();
            auto id = QUuid::fromString(stringId);
            assignedPlayerIds << id;
        }
        return assignedPlayerIds;
    }
    QVector<QString> createPlayerNamesFromJsonArray(const QJsonArray & arr) const
    {
        QVector<QString> playerNames;
        for (const auto &jsonValue : arr)
            playerNames << jsonValue.toString();
        return playerNames;
    }
};

#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
