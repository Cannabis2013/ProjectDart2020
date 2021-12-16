#ifndef DARTSINPUTBUILDER_H
#define DARTSINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonvalue.h>
#include <qjsonarray.h>
#include "qjsonobject.h"
#include "DartsModelsContext/InputServices/dartsinput.h"
#include "DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h"
class DartsInputBuilder : public IDartsInputBuilder<IModel<QUuid>,AbstractDartsInput,QByteArray,DIptVals>
{
public:
    virtual QVector<Model *> convert(const Json &byteArray) const override
    {
        try {
            auto json = fromByteArray(byteArray);
            auto arr = json.value("InputModels").toArray();
            return toJsonArray(arr);
        }  catch (const char *msg) {
            qDebug() << msg;
        }
        return QVector<Model*>();
    }
    virtual SuperModel *convert(ctrlVals vals, const QUuid &tournamentId, const QUuid &playerId, const int &hint) const override
    {
        auto input = new DartsInput;
        input->setScore(vals.score);
        input->setPoint(vals.point);
        input->setRemainingScore(vals.remainingScore);
        input->setModKeyCode(vals.modKeyCode);
        input->setRoundIndex(vals.roundIndex);
        input->setSetIndex(vals.setIndex);
        input->setAttempt(vals.attempt);
        input->setInGame(vals.inGame);
        input->setMiddleValue(vals.mid);
        input->setCurrentMinimum(vals.min);
        input->setCurrentMaximum(vals.max);
        input->setPlayerName(vals.playerName);
        input->setPlayerId(playerId);
        input->setTournamentId(tournamentId);
        input->setHint(hint);
        input->setId(QUuid::createUuid());
        return input;
    }
private:
    QJsonObject fromByteArray(const QByteArray &byteArray) const
    {
        auto document = QJsonDocument::fromJson(byteArray);
        if(!document.isObject())
            throw "ERROR! NOT JSON OBJECT";
        return document.object();
    }
    QVector<IModel<QUuid> *> toJsonArray(const QJsonArray &arr) const
    {
        QVector<IModel<QUuid>*> list;
        for (const auto& jsonValue : arr)
            list << toInputModel(jsonValue.toObject());
        return list;
    }
    AbstractDartsInput *toInputModel(const QJsonObject& obj) const
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
        inputModel->setHint(obj.value("hint").toInt());
        inputModel->setMiddleValue(obj.value("middleValue").toDouble());
        inputModel->setCurrentMaximum(obj.value("maximumValue").toInt());
        inputModel->setCurrentMinimum(obj.value("minimumValue").toInt());
        inputModel->setRemainingScore(obj.value("remainingScore").toInt());
        inputModel->setInGame(obj.value("inGame").toBool());
        return inputModel;
    }
    QUuid toId(const QJsonObject &obj, const QString &key) const
    {
        auto id = obj.value(key).toString();
        return QUuid::fromString(id);
    }
};
#endif // DARTSINPUTJSONEXTRACTOR_H
