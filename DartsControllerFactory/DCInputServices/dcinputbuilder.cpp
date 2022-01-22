#include "dcinputbuilder.h"
#include <Models/dcinput.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

DCInputBuilder::Model DCInputBuilder::create(const ByteArray &byteArray, const int &remainingScore) const
{
    return toModel(QJsonDocument::fromJson(byteArray).object(),remainingScore);
}

DCInputBuilder::Model DCInputBuilder::create(const Json &json, const int &remainingScore) const
{
    return toModel(json,remainingScore);
}

DCInputBuilder::Model DCInputBuilder::create() const
{
    return DCInput();
}

DCInputBuilder::Json DCInputBuilder::create(const Model &model) const
{
    return toJson(model);
}

DCInputBuilder::Model DCInputBuilder::create(const Json &json) const
{
    return toModel(json);
}

QJsonObject DCInputBuilder::toJson(const Model &model) const
{
    QJsonObject obj;
    obj["point"] = model.point;
    obj["score"] = model.score;
    obj["remainingScore"] = model.remScore;
    obj["roundIndex"] = model.roundIndex;
    obj["playerIndex"] = model.playerIndex;
    obj["attemptIndex"] = model.attemptIndex;
    obj["inputPlayerName"] = model.playerName;
    obj["modKeyCode"] = model.modKeyCode;
    obj["minimumValue"] = model.min;
    obj["middleValue"] = model.mid;
    obj["maximumValue"] = model.max;
    obj["inGame"] = model.inGame;
    obj["approved"] = model.approved;
    return obj;
}

QJsonObject DCInputBuilder::toJson(const ByteArray &byteArray) const {return Doc::fromJson(byteArray).object();}

DCInputBuilder::Model DCInputBuilder::toModel(const Json &json, const int &remainingScore) const
{
    DCInput ipt;
    ipt.point = json.value("point").toInt();
    ipt.score = json.value("score").toInt();
    ipt.modKeyCode = json.value("modKeyCode").toInt();
    ipt.remScore = json.value("remainingScore").toInt(remainingScore);
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
