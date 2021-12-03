#ifndef DSCINPUTBUILDER_H
#define DSCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsController/DCInputSLAs/abstractdcinputbuilder.h"
class DSCInputBuilder : public AbstractDCInputBuilder
{
public:
    DSCInputBuilder(IDCMetaCtx *metaCtx, IDCCalcScore *scoreCalc, IndexCtrl *indexCtrl,
                    ScoresCtx *scoresCtx, PlayersCtx *playersCtx)
    {
        setMetaCtx(metaCtx);
        setInputScoreCtx(scoreCalc);
        setIndexCtrl(indexCtrl);
        setScoresCtx(scoresCtx);
        setPlayersCtx(playersCtx);
    }
    virtual DCIptVals create(const QByteArray &json) const override
    {
        auto input = toInput(toJsonObject(json));
        auto setIndex = indexCtrl()->index().setIndex;
        input.playerName = scoresCtx()->scores().at(setIndex).name;
        input.score = inputScoreCtx()->calc(input);
        input.remainingScore = scoresCtx()->score(input.playerName).remainingScore;
        input.inGame = playersContext()->status(input.playerName);
        addIndex(input,indexCtrl()->index());
        return input;
    }
private:
    DCIptVals toInput(const QJsonObject &obj, const int &initialScore = -1) const
    {
        DCIptVals input;
        input.playerId = toId(obj.value("inputPlayerId").toString());
        input.playerName = obj.value("inputPlayerName").toString();
        input.score = obj.value("score").toInt();
        input.mid = obj.value("middleValue").toDouble(0);
        input.min = obj.value("minimumValue").toInt(0);
        input.max = obj.value("maximumValue").toInt(0);
        input.remainingScore = obj.value("remainingScore").toInt(initialScore);
        input.approved = obj.value("approved").toBool(false);
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
    void addIndex(DCIptVals &input, const DCIndex &index) const
    {
        input.roundIndex = index.roundIndex;
        input.setIndex = index.setIndex;
        input.attempt = index.attemptIndex;
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
