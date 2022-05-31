#include "dartsjsonconverter.h"

#include <qjsondocument.h>

DartsJsonConverter::Json DartsJsonConverter::convert(Model *m) const
{
    return toJsonObject(dynamic_cast<IDartsTournament*>(m));
}

DartsJsonConverter::Model *DartsJsonConverter::convert(const ByteArray &byteArray) const
{
    return convert(QJsonDocument::fromJson(byteArray).object());
}

DartsJsonConverter::Model *DartsJsonConverter::convert(const Json &d) const
{
    return fromJsonObject(d);
}

QJsonObject DartsJsonConverter::toJsonObject(IDartsTournament *model) const
{
    QJsonObject obj;
    obj["tournamentId"] = model->id().toString(QUuid::WithoutBraces);
    obj["title"] = model->title();
    obj["gameMode"] = model->gameMode();
    obj["initRemScore"] = model->initialRemaining();
    obj["inputHint"] = model->inputHint();
    obj["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
    obj["winnerName"] = model->winnerName();
    fromPlayerDetails(model,obj);
    obj["totalTurns"] = model->totalTurns();
    obj["turnIndex"] = model->turnIndex();
    obj["roundIndex"] = model->roundIndex();
    obj["playerIndex"] = model->setIndex();
    obj["attemptIndex"] = model->attemptIndex();
    return obj;
}

void DartsJsonConverter::fromPlayerDetails(IModel<QUuid> *model, QJsonObject &obj) const
{
    QJsonArray arr;
    auto tournament = dynamic_cast<IDartsTournament*>(model);
    auto count = tournament->playerNames().count();
    for (int i = 0; i < count; ++i) {
        auto id = tournament->playerIds().at(i);
        auto name = tournament->playerNames().at(i);
        arr << toJsonObject(id,name);
    }
    obj["assignedPlayersCount"] = count;
    obj["assignedPlayerDetails"] = arr;
}

QJsonObject DartsJsonConverter::toJsonObject(const QUuid &id, const QString &name) const
{
    QJsonObject obj;
    obj["playerId"] = id.toString(QUuid::WithoutBraces);
    obj["playerName"] = name;
    return obj;
}

IDartsTournament *DartsJsonConverter::fromJsonObject(const QJsonObject &obj) const
{
    auto tournament = new DartsTournament;
    tournament->setId(toId(obj,"tournamentId",QUuid::createUuid().toString(QUuid::WithoutBraces)));
    tournament->setTitle(obj.value("title").toString());
    tournament->setGameMode(obj.value("gameMode").toInt());
    tournament->setKeyPoint(obj.value("initRemScore").toInt());
    tournament->setInputHint(obj.value("inputHint").toInt());
    tournament->setStatus(obj.value("status").toInt());
    tournament->setWinnerId(toId(obj,"winnerId"));
    tournament->setWinnerName(obj.value("winnerName").toString(""));
    tournament->setTotalTurns(obj.value("totalTurns").toInt(0));
    tournament->setTurnIndex(obj.value("turnIndex").toInt(0));
    tournament->setRoundIndex(obj.value("roundIndex").toInt(1));
    tournament->setSetIndex(obj.value("playerIndex").toInt(0));
    tournament->setAttemptIndex(obj.value("attemptIndex").toInt(0));
    setTournamentPlayerDetails(tournament,obj);
    return tournament;
}

void DartsJsonConverter::setTournamentPlayerDetails(DartsTournament *tournament, const QJsonObject &obj) const
{
    QVector<QUuid> playerIds;
    QVector<QString> playerNames;
    auto arr = obj.value("assignedPlayerDetails").toArray();
    for (const auto &jsonvalue : qAsConst(arr)) {
        auto jsonObject = jsonvalue.toObject();
        playerIds << QUuid::fromString(jsonObject.value("playerId").toString());
        playerNames << jsonObject.value("playerName").toString();
    }
    tournament->setPlayerIds(playerIds);
    tournament->setPlayerNames(playerNames);
}

QUuid DartsJsonConverter::toId(const QJsonObject &obj, const QString &key, const QString &defaultvalue) const
{
    return QUuid::fromString(obj.value(key).toString(defaultvalue));
}

