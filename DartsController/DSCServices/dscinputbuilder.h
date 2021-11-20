#ifndef DSCINPUTBUILDER_H
#define DSCINPUTBUILDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsModelsContext/InputServices/dartsinput.h"
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
    virtual AbstractDartsInput *create(const QByteArray &json) const override
    {
        auto input = toInput(toJsonObject(json));
        auto setIndex = indexCtrl()->index()->setIndex();
        input->setId(QUuid::createUuid());
        input->setTournamentId(metaCtx()->get().tournamentId);
        input->setPlayerId(scoresCtx()->scores().at(setIndex).playerId);
        input->setPlayerName(scoresCtx()->scores().at(setIndex).playerName);
        input->setScore(inputScoreCtx()->calculate(input));
        input->setRemainingScore(scoresCtx()->score(input->playerId()).remainingScore);
        input->setInGame(playersContext()->status(input->playerId()));
        addIndex(input,indexCtrl()->index());
        return input;
    }
    virtual AbstractDartsInput *createDefault() const override
    {
        auto input = new DartsInput;
        auto meta = metaCtx()->get();
        input->setRemainingScore(meta.initialRemainingScore);
        input->setRoundIndex(1);
        input->setTournamentId(meta.tournamentId);
        input->setPlayerId(meta.currentPlayerId);
        input->setPlayerName(meta.currentPlayerName);
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
