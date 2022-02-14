#include "dcinputconverter.h"
#include <qjsonobject.h>
#include "Models/dcinput.h"

DCInputConverter::Model DCInputConverter::convert(const QJsonObject &json) const
{
    DCInput ipt;
    ipt.point = json.value("point").toInt();
    ipt.score = json.value("score").toInt();
    ipt.modKeyCode = json.value("modKeyCode").toInt();
    ipt.remScore = json.value("remainingScore").toInt();
    ipt.playerName = json.value("inputPlayerName").toString();
    ipt.inGame = json.value("inGame").toBool();
    ipt.roundIndex = json.value("roundIndex").toInt();
    ipt.playerIndex = json.value("playerIndex").toInt();
    ipt.attemptIndex = json.value("attemptIndex").toInt();
    ipt.min = json.value("currentMinimum").toInt();
    ipt.mid = json.value("middleValue").toDouble();
    ipt.max = json.value("currentMaximum").toInt();
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
    obj["roundIndex"] = model.roundIndex;
    obj["playerIndex"] = model.playerIndex;
    obj["attemptIndex"] = model.attemptIndex;
    obj["inputPlayerId"] = model.playerId.toString(QUuid::WithoutBraces);
    obj["inputPlayerName"] = model.playerName;
    obj["modKeyCode"] = model.modKeyCode;
    obj["minimumValue"] = model.min;
    obj["middleValue"] = model.mid;
    obj["maximumValue"] = model.max;
    obj["inGame"] = model.inGame;
    obj["approved"] = model.approved;
    return obj;
}
