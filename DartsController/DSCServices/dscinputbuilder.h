#ifndef DSCINPUTBUILDER_H
#define DSCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
#include "DartsController/DCInputSLAs/idcinputbuilder.h"
class DSCInputBuilder : public IDCInputBuilder
{
public:
    virtual AbstractDartsInput *create(const QByteArray &json, const IDCPlayerController *playerController,
                                       const IDCCalcScore *getScoreContext,IDartsIndex *index, IDCScoreModels *scoreModels) const override
    {
        auto input = toInput(toJsonObject(json));
        input->setPlayerId(scoreModels->scores().at(index->setIndex()).playerId);
        input->setPlayerName(scoreModels->scores().at(index->setIndex()).playerName);
        input->setScore(getScoreContext->calculate(input));
        input->setRemainingScore(scoreModels->score(input->playerId()).remainingScore);
        input->setInGame(playerController->status(input->playerId()));
        addIndex(input,index);
        return input;
    }
private:
    AbstractDartsInput *toInput(const DCScoreModel &scoreModel) const
    {
        auto input = new DartsInput;
        input->setPlayerId(scoreModel.playerId);
        input->setPlayerName(scoreModel.playerName);
        input->setRemainingScore(scoreModel.remainingScore);
        return input;
    }
    AbstractDartsInput *toInput(const QJsonObject &obj, const int &initialScore = -1) const
    {
        auto input = new DartsInput;
        input->setPlayerId(toId(obj.value("inputPlayerId").toString()));
        input->setPlayerName(obj.value("inputPlayerName").toString());
        input->setScore(obj.value("score").toInt());
        input->setRemainingScore(obj.value("totalScore").toInt());
        input->setMiddleValue(obj.value("middleValue").toDouble(0));
        input->setCurrentMinimum(obj.value("minimumValue").toInt(0));
        input->setCurrentMaximum(obj.value("maximumValue").toInt(0));
        input->setRemainingScore(obj.value("remainingScore").toInt(initialScore));
        input->setApproved(obj.value("approved").toBool(false));
        return input ;
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
    QUuid toId(const QString &stringId) const
    {
        return QUuid::fromString(stringId);
    }
    void addIndex(AbstractDartsInput *input, IDartsIndex *index) const
    {
        input->setRoundIndex(index->roundIndex());
        input->setSetIndex(index->setIndex());
        input->setAttempt(index->attemptIndex());
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
