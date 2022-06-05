#include "dcinputconverter.h"
#include <qjsonobject.h>
#include <DartsController/Models/dcinput.h>

DCInputConverter::Model DCInputConverter::convert(const QJsonObject &json) const
{
    DCInput ipt;
    ipt.point = json.value("point").toInt();
    ipt.score = json.value("score").toInt();
    ipt.modKeyCode = json.value("modKeyCode").toInt();
    ipt.remScore = json.value("remainingScore").toInt();
    ipt.playerName = json.value("inputPlayerName").toString();
    ipt.inGame = json.value("inGame").toBool();
    ipt.index.roundIndex = json.value("roundIndex").toInt();
    ipt.index.playerIndex = json.value("playerIndex").toInt();
    ipt.index.attemptIndex = json.value("attemptIndex").toInt();
    ipt.approved = json.value("approved").toBool();
    return ipt;
}

QJsonObject DCInputConverter::convert(const Model &model) const
{
    QJsonObject obj;
    obj["point"] = model.point;
    obj["score"] = model.score;
    obj["tournamentId"] = model.tournamentId.toString(QUuid::WithoutBraces);
    obj["remainingScore"] = model.remScore;
    obj["roundIndex"] = model.index.roundIndex;
    obj["playerIndex"] = model.index.playerIndex;
    obj["attemptIndex"] = model.index.attemptIndex;
    obj["inputPlayerId"] = model.playerId.toString(QUuid::WithoutBraces);
    obj["inputPlayerName"] = model.playerName;
    obj["modKeyCode"] = model.modKeyCode;
    obj["inGame"] = model.inGame;
    obj["approved"] = model.approved;
    return obj;
}
