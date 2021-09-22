#ifndef DSCCREATEINPUTMODELS_H
#define DSCCREATEINPUTMODELS_H

#include "dcinputmodel.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <idccreateinputmodel.h>

class DSCCreateInputModel : public IDCCreateInputModel
{
public:
    DCContext::IDCInputModel *createModel(const QByteArray &json, const IJsonValuesExtractor *extractor) const override
    {
        return toModel(toJsonObject(json),extractor);
    }

    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const override
    {
        auto inputModel = DCContext::DCInputModel::createInstance();
        inputModel->setPlayerId(scoreModel.id);
        inputModel->setPlayerName(scoreModel.name);
        inputModel->setTotalScore(scoreModel.totalScore);
        return inputModel;
    }
private:
    DCContext::IDCInputModel *toModel(const DCContext::DCScoreModel &model) const
    {
        auto scoreModel = DCContext::DCInputModel::createInstance();
        scoreModel->setPlayerId(model.id);
        scoreModel->setPlayerName(model.name);
        scoreModel->setTotalScore(model.totalScore);
        return scoreModel;
    }
    DCContext::IDCInputModel *toModel(const QJsonObject &obj, const IJsonValuesExtractor *extractor) const
    {
        auto scoreModel = DCContext::DCInputModel::createInstance();
        scoreModel->setPlayerId(extractor->toId(obj,"playerId"));
        scoreModel->setPlayerName(extractor->toString(obj,"playerName"));
        scoreModel->setScore(extractor->toInt(obj,"score"));
        scoreModel->setTournamentId(extractor->toId(obj,"tournamentId"));
        return scoreModel;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
