#ifndef DARTSTOURNAMENTBUILDER_H
#define DARTSTOURNAMENTBUILDER_H

#include <qjsondocument.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "dartstournament.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartstournamentbuilder.h"

class DartsTournamentBuilder : public IDartsTournamentBuilder
{
public:
    virtual IModel<QUuid> *buildTournament(const QByteArray &json) const override
    {
        QJsonObject obj;
        try {
            obj = toJsonobject(json);
        }  catch (const char *msg) {
            return nullptr;
        }
        return toModel(obj);
    }
    virtual QVector<IModel<QUuid> *> createTournaments(const QByteArray &json) const override
    {
        QJsonArray arr;
        try {
            arr = toJsonArray(json);
        }  catch (const char *msg) {
            return QVector<IModel<QUuid>*>();
        }
        return toModels(arr);
    }
private:
    QJsonObject toJsonobject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "ERROR! NOT OBJECT!";
        return document.object();;
    }
    const QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isArray())
            throw "ERROR! NOT ARRAY!";
        return document.array();
    }
    const QVector<IModel<QUuid>*> toModels(const QJsonArray &arr) const
    {
        QVector<IModel<QUuid>*> list;
        for (const auto& jsonValue : arr)
            list << toModel(jsonValue.toObject());
        return list;
    }
    AbstractDartsTournament* toModel(const QJsonObject& obj) const
    {
        auto dartsTournamentModel = ModelsContext::DartsTournament::createInstance();
        dartsTournamentModel->setId(QUuid(obj.value("tournamentId").toString(QUuid::createUuid().toString(QUuid::WithoutBraces))));
        dartsTournamentModel->setTitle(obj.value("title").toString());
        dartsTournamentModel->setGameMode(obj.value("gameMode").toInt());
        dartsTournamentModel->setKeyPoint(obj.value("keyPoint").toInt());
        dartsTournamentModel->setDisplayHint(obj.value("displayHint").toInt());
        dartsTournamentModel->setInputMode(obj.value("inputHint").toInt());
        dartsTournamentModel->setStatus(obj.value("status").toInt());
        dartsTournamentModel->setWinnerId(QUuid(obj.value("winnerId").toString("")));
        dartsTournamentModel->setWinnerName(obj.value("winnerName").toString(""));
        setTournamentPlayerDetails(dartsTournamentModel,obj);
        return dartsTournamentModel;
    }
    void setTournamentPlayerDetails(ModelsContext::DartsTournament *tournament, const QJsonObject &obj) const
    {
        QVector<QUuid> playerIds;
        QVector<QString> playerNames;
        auto arr = obj.value("assignedPlayerDetails").toArray();
        for (const auto &jsonvalue : arr) {
            auto jsonObject = jsonvalue.toObject();
            playerIds << QUuid::fromString(jsonObject.value("playerId").toString());
            playerNames << jsonObject.value("playerName").toString();
        }
        tournament->setAssignedPlayerIdentities(playerIds);
        tournament->setAssignedPlayerNames(playerNames);
    }
};
#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
