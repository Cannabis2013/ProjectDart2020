#include "dartsinputbuilder.h"
QVector<IModel<QUuid> *> DartsInputBuilder::createInputs(const QByteArray &json) const
{
    auto arr = QJsonDocument::fromJson(json).array();
    return createInputsFromJsonArray(arr);
}

QVector<IModel<QUuid>*> DartsInputBuilder::createInputsFromJsonArray(const QJsonArray &arr) const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& jsonValue : arr)
        list << toInputModel(jsonValue.toObject());
    return list;
}

AbstractDartsInput *DartsInputBuilder::toInputModel(const QJsonObject &obj) const
{
    auto inputModel = new DartsInput;
    inputModel->setId(obj.value("id").toString(QUuid::createUuid().toString(QUuid::WithoutBraces)));
    inputModel->setTournamentId(toId(obj,"tournamentId"));
    inputModel->setPlayerId(toId(obj,"inputPlayerId"));
    inputModel->setPlayerName(obj.value("inputPlayerName").toString());
    inputModel->setRoundIndex(obj["roundIndex"].toInt());
    inputModel->setSetIndex(obj["setIndex"].toInt());
    inputModel->setAttempt(obj["attemptIndex"].toInt());
    inputModel->setPoint(obj.value("point").toInt());
    inputModel->setScore(obj.value("score").toInt());
    inputModel->setModKeyCode(obj["modKeyCode"].toInt());
    inputModel->setHint(obj.value("hint").toInt(DisplayHint));
    inputModel->setMiddleValue(obj.value("middleValue").toDouble());
    inputModel->setCurrentMaximum(obj.value("maximumValue").toInt());
    inputModel->setCurrentMinimum(obj.value("minimumValue").toInt());
    inputModel->setRemainingScore(obj.value("remainingScore").toInt());
    inputModel->setInGame(obj.value("inGame").toBool());
    return inputModel;
}

QUuid DartsInputBuilder::toId(const QJsonObject &obj, const QString &key) const
{
    auto id = obj.value(key).toString();
    return QUuid::fromString(id);
}
