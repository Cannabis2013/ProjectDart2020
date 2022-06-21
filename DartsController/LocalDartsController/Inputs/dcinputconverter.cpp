#include "dcinputconverter.h"
#include <qjsonobject.h>
#include <DartsController/Contracts/Models/dcinput.h>

DCInputConverter::Model DCInputConverter::convert(const QJsonObject &json) const
{
        DCInput input;
        input.point = json.value("point").toInt();
        input.score = json.value("score").toInt();
        input.modKeyCode = json.value("modKeyCode").toInt();
        input.remScore = json.value("remainingScore").toInt();
        input.playerName = json.value("inputPlayerName").toString();
        input.inGame = json.value("inGame").toBool();
        input.index.roundIndex = json.value("roundIndex").toInt();
        input.index.playerIndex = json.value("playerIndex").toInt();
        input.index.attemptIndex = json.value("attemptIndex").toInt();
        input.approved = json.value("approved").toBool();
        return input;
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
