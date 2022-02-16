#include "dcgetturnvaluesasjson.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include <qjsondocument.h>

DCGetTurnValuesAsJson::DCGetTurnValuesAsJson(DCServices *services)
{
    _indexController = services->indexServices()->indexController();
    _playerManager = services->playerServices()->playerManager();
    _createFinishes = services->finServices()->finishBuilder();
}

QByteArray DCGetTurnValuesAsJson::toJson() const
{
    auto index = _indexController->index();
    auto player = _playerManager->player(index.playerIndex);
    auto finish = _createFinishes->suggestTargetRow(player.remaining,index.attemptIndex);
    auto turnValuesAsJson = toJson(index,player,finish);
    auto turnValuesAsBa = toByteArray(turnValuesAsJson);
    return turnValuesAsBa;
}

QJsonObject DCGetTurnValuesAsJson::toJson(const DCIndex &index, const DCPlayer &player, const QString &finish) const
{
    QJsonObject json;
    json["canUndo"] = index.turnIndex > 0;
    json["canRedo"] = index.turnIndex < index.totalTurns;
    json["currentAttemptIndex"] = index.attemptIndex;
    json["currentRoundIndex"] = index.roundIndex;
    json["currentPlayerName"] = player.name;
    json["currentPlayerIndex"] = index.playerIndex;
    json["finishCandidate"] = finish;
    return json;
}

QByteArray DCGetTurnValuesAsJson::toByteArray(const QJsonObject &json) const
{
    auto jsonDoc = QJsonDocument(json);
    auto byteArray = jsonDoc.toJson();
    return byteArray;
}