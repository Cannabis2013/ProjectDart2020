#ifndef DARTSBUILDER_H
#define DARTSBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
#include "DartsModelsContext/TournamentModels/dartstournament.h"
#include "DartsModelsContext/TournamentsDbSLAs/idartsbuilder.h"
class DartsBuilder : public IDartsBuilder<IModel<QUuid>,IDartsTournament,QByteArray,TnmVals>
{
public:
    virtual SuperModel *createModel(const QByteArray &json) const override
    {
        QJsonObject obj;
        try {obj = fromByteArray(json);}
        catch (...) {return nullptr;}
        return toModel(obj);
    }
    virtual TransitModel convert(SuperModel *tournament) const override
    {
        TnmVals vals;
        vals.tournamentId = tournament->id();
        vals.entryRestricted = tournament->entryRestricted();
        vals.winnerName = tournament->winnerName();
        vals.playerCount = tournament->playerNames().count();
        vals.initRem = tournament->initialRemaining();
        return vals;
    }
private:
    QJsonObject fromByteArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject()) throw "ERROR! NOT OBJECT!";
        return document.object();;
    }
    const QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isArray()) throw "ERROR! NOT ARRAY!";
        return document.array();
    }
    const QVector<IModel<QUuid>*> toModels(const QJsonArray &arr) const
    {
        QVector<IModel<QUuid>*> list;
        for (const auto& jsonValue : arr)
            list << toModel(jsonValue.toObject());
        return list;
    }
    IDartsTournament* toModel(const QJsonObject& obj) const
    {
        auto tournament = new DartsTournament;
        tournament->setId(toId(obj,"tournamentId",QUuid::createUuid().toString(QUuid::WithoutBraces)));
        tournament->setTitle(obj.value("title").toString());
        tournament->setGameMode(obj.value("gameMode").toInt());
        tournament->setKeyPoint(obj.value("initRemScore").toInt());
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
        tournament->setPlayerIds(playerIds);
        tournament->setPlayerNames(playerNames);
    }
    QUuid toId(const QJsonObject &obj, const QString &key, const QString &defaultvalue = "") const
    {
        return QUuid::fromString(obj.value(key).toString(defaultvalue));
    }
};
#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
