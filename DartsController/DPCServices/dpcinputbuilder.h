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
                    ScoresCtx *scoresCtx, PlayersCtx *playersCtx)
    {
        setMetaCtx(metaCtx);
        setInputScoreCtx(scoreCalc);
        setIndexCtrl(indexCtrl);
        setScoresCtx(scoresCtx);
        setPlayersCtx(playersCtx);
    }
    virtual AbstractDartsInput *create(const QByteArray &json) const override
    {
        auto jsonObject = toJsonObject(json);
        auto input = toModel(jsonObject);
        auto setIndex = indexCtrl()->index()->setIndex();
        auto meta = metaCtx()->get();
        input->setId(QUuid::createUuid());
        input->setTournamentId(meta.tournamentId);
        input->setPlayerId(scoresCtx()->scores().at(setIndex).playerId);
        input->setPlayerName(scoresCtx()->scores().at(setIndex).playerName);
        input->setScore(inputScoreCtx()->calculate(input));
        input->setRemainingScore(scoresCtx()->score(input->playerId()).remainingScore);
        input->setInGame(false);
        addIndex(input,indexCtrl()->index());
        return input;
    }
    virtual AbstractDartsInput *createDefault() const override
    {
        auto input = new DartsInput;
        auto meta = metaCtx()->get();
        input->setRemainingScore(meta.initialRemainingScore);
        input->setRoundIndex(1);
        return input;
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
    void addIndex(AbstractDartsInput *input, IDartsIndex *index) const
    {
        input->setRoundIndex(index->roundIndex());
        input->setSetIndex(index->setIndex());
        input->setAttempt(index->attemptIndex());
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
