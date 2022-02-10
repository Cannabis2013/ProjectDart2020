#include "dartsbuilder.h"

DartsBuilder::Model *DartsBuilder::createModel(const QByteArray &json) const
{
    QJsonObject obj;
    try {obj = fromByteArray(json);}
    catch (...) {return nullptr;}
    return toModel(obj);
}

DartsBuilder::Model *DartsBuilder::createInitial(std::function<void(Model*)> initializer) const
{
    auto tournament = create();
    initializer(tournament);
    return tournament;
}

DartsTournament *DartsBuilder::create() const
{
    auto tournament = new DartsTournament;
    tournament->setGameMode(DARTS_GAMEMODE);
    return tournament;
}

QJsonObject DartsBuilder::fromByteArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    if(!document.isObject()) throw "ERROR! NOT OBJECT!";
    return document.object();;
}

const QJsonArray DartsBuilder::toJsonArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    if(!document.isArray()) throw "ERROR! NOT ARRAY!";
    return document.array();
}

const QVector<IModel<QUuid> *> DartsBuilder::toModels(const QJsonArray &arr) const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& jsonValue : arr)
        list << toModel(jsonValue.toObject());
    return list;
}

DartsTournament *DartsBuilder::toModel(const QJsonObject &obj) const
{
    auto tournament = create();
    tournament->setId(toId(obj,"tournamentId",QUuid::createUuid().toString(QUuid::WithoutBraces)));
    tournament->setTitle(obj.value("title").toString());
    tournament->setKeyPoint(obj.value("initRemScore").toInt());
    tournament->setInputHint(obj.value("inputHint").toInt());
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

void DartsBuilder::setTournamentPlayerDetails(DartsTournament *tournament, const QJsonObject &obj) const
{
    QVector<QUuid> playerIds;
    QVector<QString> playerNames;
    auto arr = obj.value("players").toArray();
    for (const auto &jsonvalue : qAsConst(arr)) {
        auto jsonObject = jsonvalue.toObject();
        playerIds << QUuid::fromString(jsonObject.value("playerId").toString());
        playerNames << jsonObject.value("playerName").toString();
    }
    tournament->setPlayerIds(playerIds);
    tournament->setPlayerNames(playerNames);
}

QUuid DartsBuilder::toId(const QJsonObject &obj, const QString &key, const QString &defaultvalue) const
{
    return QUuid::fromString(obj.value(key).toString(defaultvalue));
}
