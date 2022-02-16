#include "dartsinputconverter.h"
#include "InputsDbSLAs/idartsinputbuilder.h"

DartsInputConverter::Json DartsInputConverter::create(Model *model) const
{
    if(model != nullptr)
        return toJsonObject(model);
    else
        return Json();
}

DartsInputConverter::Model *DartsInputConverter::create(const Json &json) const
{
    return toModel(json);
}

DartsInputConverter::Model *DartsInputConverter::create(const ByteArray &byteArray) const
{
    auto json = fromByteArray(byteArray);
    return create(json);
}

QJsonObject DartsInputConverter::fromByteArray(const QByteArray &byteArray) const
{
    return QJsonDocument::fromJson(byteArray).object();
}

QJsonArray DartsInputConverter::toJsonArray(const QVector<IModel<QUuid> *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << toJsonObject(model);
    return arr;
}

QJsonObject DartsInputConverter::toJsonObject(IModel<QUuid> *model) const
{
    auto inputModel = dynamic_cast<const IDartsInput*>(model);
    QJsonObject obj;
    obj["id"] = inputModel->id().toString(QUuid::WithoutBraces);
    obj["tournamentId"] = inputModel->tournamentId().toString(QUuid::WithoutBraces);
    obj["point"] = inputModel->point();
    obj["score"] = inputModel->score();
    obj["remainingScore"] = inputModel->remainingScore();
    obj["roundIndex"] = inputModel->roundIndex();
    obj["playerIndex"] = inputModel->playerIndex();
    obj["attemptIndex"] = inputModel->attempt();
    obj["inputPlayerId"] = inputModel->playerId().toString(QUuid::WithoutBraces);
    obj["inputPlayerName"] = inputModel->playerName();
    obj["hint"] = inputModel->hint();
    obj["modKeyCode"] = inputModel->modKeyCode();
    obj["inGame"] = inputModel->inGame();
    obj["approved"] = inputModel->approved();
    return obj;
}

DartsInputConverter::Model *DartsInputConverter::toModel(const Json &json) const
{
    auto model = new DartsInput;
    model->setId(json.value("id").toString(QUuid::createUuid().toString(QUuid::WithoutBraces)));
    model->setTournamentId(QUuid::fromString(json.value("tournamentId").toString()));
    model->setPoint(json.value("point").toInt());
    model->setScore(json.value("score").toInt());
    model->setRemainingScore(json.value("remainingScore").toInt());
    model->setModKeyCode(json.value("modKeyCode").toInt());
    model->setPlayerId(QUuid::fromString(json.value("inputPlayerId").toString()));
    model->setPlayerName(json.value("inputPlayerName").toString());
    model->setHint(json.value("hint").toInt());
    model->setInGame(json.value("inGame").toBool());
    model->setRoundIndex(json.value("roundIndex").toInt());
    model->setPlayerIndex(json.value("playerIndex").toInt());
    model->setAttempt(json.value("attemptIndex").toInt());
    model->setApproved(json.value("approved").toBool());
    return model;
}
