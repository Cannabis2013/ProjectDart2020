#ifndef DPCINPUTBUILDER_H
#define DPCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
class DPCInputBuilder : public AbstractDCInputBuilder
{
public:
    DPCInputBuilder(IDCMetaCtx *metaCtx, IDCCalcScore *scoreCalc, IndexCtrl *indexCtrl,
                    ScoresCtx *scoresCtx, PlayersCtx *playersCtx):
        AbstractDCInputBuilder(metaCtx,scoreCalc,indexCtrl,scoresCtx,playersCtx){}
    DCIptVals create(const QByteArray &json) const override
    {
        auto input = toModel(toJsonObject(json));
        auto setIndex = indexCtrl()->index().setIndex;
        input.playerName = scoresCtx()->scores().at(setIndex).name;
        input.score = inputScoreCtx()->calc(input);
        input.remainingScore = scoresCtx()->score(input.playerName).remScore;
        input.inGame = false;
        addIndex(input,indexCtrl()->index());
        return input;
    }
    DCIptVals create() const override
    {
        DCIptVals input;
        auto setIndex = indexCtrl()->index().setIndex;
        input.playerName = scoresCtx()->scores().at(setIndex).name;
        input.score = 0;
        input.remainingScore = metaCtx()->get().initRemScore;
        input.inGame = true;
        return input;
    }
private:
    DCIptVals toModel(const QJsonObject &obj, const int &initialScore = -1) const
    {
        DCIptVals input;
        input.playerId = toId(obj.value("inputPlayerId").toString(""));
        input.playerName = obj.value("inputPlayerName").toString("");
        input.score = obj.value("score").toInt(0);
        input.remainingScore = obj.value("remainingScore").toInt(initialScore);
        input.point = obj.value("point").toInt(0);
        input.modKeyCode = obj.value("modKeyCode").toInt(0);
        input.mid = obj.value("middleValue").toDouble(0);
        input.min = obj.value("minimumValue").toInt(0);
        input.max = obj.value("maximumValue").toInt(0);
        input.inGame = obj.value("inGame").toBool(false);
        return input;
    }
    AbstractDartsInput *toModel(const DCScoreModel &scoreModel) const
    {
        auto input = new DartsInput;
        input->setPlayerName(scoreModel.name);
        input->setRemainingScore(scoreModel.remScore);
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
    void addIndex(DCIptVals &input, const DCIndex &index) const
    {
        input.roundIndex = index.roundIndex;
        input.setIndex = index.setIndex;
        input.attempt = index.attemptIndex;
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
