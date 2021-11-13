#ifndef DPCINPUTBUILDER_H
#define DPCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"
class DPCInputBuilder : public IDCInputBuilder
{
public:
    virtual AbstractDartsInput *create(const QByteArray &json, const IDCPlayerController *playerController,
                               const IDCCalcScore *calcScoreContext,IDartsIndex *index, IDCScoreModels *scoreModels) const override
    {
        auto jsonObject = toJsonObject(json);
        auto input = toModel(jsonObject);
        input->setPlayerId(scoreModels->scores().at(index->setIndex()).playerId);
        input->setPlayerName(scoreModels->scores().at(index->setIndex()).playerName);
        input->setScore(calcScoreContext->calculate(input));
        input->setRemainingScore(scoreModels->score(input->playerId()).remainingScore);
        input->setInGame(playerController->status(input->playerId()));
        return input;
    }
    AbstractDartsInput *create(const QByteArray &json, const int &initialScore) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject,initialScore);
    }
    AbstractDartsInput *create(const DCScoreModel &scoreModel) const override
    {
        return toModel(scoreModel);
    }
    QVector<AbstractDartsInput *> buildInputs(IDCScoreModels *scoresService) const override
    {
        QVector<AbstractDartsInput *> models;
        for (const auto &model : scoresService->scores())
            models << toModel(model);
        return models;
    }
    QVector<AbstractDartsInput*> buildInputs(const QJsonArray &arr) const override
    {
        QVector<AbstractDartsInput *> models;
        for (const auto &jsonVal : arr)
            models << toModel(jsonVal.toObject());
        return models;
    }
private:
    AbstractDartsInput * toModel(const QJsonObject &obj, const int &initialScore = -1) const
    {
        AbstractDartsInput * input = new DartsInput();
        input->setPlayerId(toId(obj.value("inputPlayerId").toString("")));
        input->setPlayerName(obj.value("inputPlayerName").toString(""));
        input->setScore(obj.value("score").toInt(0));
        input->setRemainingScore(obj.value("remainingScore").toInt(initialScore));
        input->setPoint(obj.value("point").toInt(0));
        input->setModKeyCode(obj.value("modKeyCode").toInt(0));
        input->setMiddleValue(obj.value("middleValue").toDouble(0));
        input->setCurrentMinimum(obj.value("minimumValue").toInt(0));
        input->setCurrentMaximum(obj.value("maximumValue").toInt(0));
        input->setInGame(obj.value("inGame").toBool(false));
        return input;
    }
    AbstractDartsInput *toModel(const DCScoreModel &scoreModel) const
    {
        auto input = new DartsInput;
        input->setPlayerId( scoreModel.playerId);
        input->setPlayerName(scoreModel.playerName);
        input->setRemainingScore(scoreModel.remainingScore);
        return input;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        return document.object();
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isArray())
            throw "JSON NOT ARRAY";
        return document.array();
    }
    QByteArray toByteArray(const QJsonValue &jsonValue) const
    {
        auto document = QJsonDocument(jsonValue.toObject());
        return document.toJson();
    }
    QUuid toId(const QString &stringId) const
    {
        return QUuid::fromString(stringId);
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
