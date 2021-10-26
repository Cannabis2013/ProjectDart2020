#ifndef DARTSTOURNAMENTBUILDER_H
#define DARTSTOURNAMENTBUILDER_H

#include <qjsondocument.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DartsModelsContext/TournamentModels/dartstournament.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h"

class DartsTournamentBuilder : public IDartsBuilder
{
public:
    virtual IModel<QUuid> *createTournament(const QByteArray &json) const override
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
        auto tournament = DartsTournament::createInstance();
        tournament->setId(toId(obj,"tournamentId"));
        tournament->setTitle(obj.value("title").toString());
        tournament->setGameMode(obj.value("gameMode").toInt());
        tournament->setKeyPoint(obj.value("keyPoint").toInt());
        tournament->setInputMode(obj.value("inputHint").toInt());
        tournament->setStatus(obj.value("status").toInt());
        tournament->setWinnerId(toId(obj,"winnerId"));
        tournament->setWinnerName(obj.value("winnerName").toString(""));
        tournament->setTotalTurns(obj.value("totalTurns").toInt(0));
        tournament->setTurnIndex(obj.value("turnIndex").toInt(0));
        tournament->setRoundIndex(obj.value("roundIndex").toInt(1));
        tournament->setSetIndex(obj.value("setIndex").toInt(0));
        tournament->setAttemptIndex(obj.value("attemptIndex").toInt(0));
        setTournamentPlayerDetails(tournament,obj);
        return tournament;
    }
    void setTournamentPlayerDetails(DartsTournament *tournament, const QJsonObject &obj) const
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
    QUuid toId(const QJsonObject &obj, const QString &key, const QString &defaultvalue = "") const
    {
        return QUuid::fromString(obj.value(key).toString(defaultvalue));
    }
};
#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
