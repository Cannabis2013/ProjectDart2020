#ifndef DSCCREATEINPUTMODELS_H
#define DSCCREATEINPUTMODELS_H

#include "DartsController/DCInputServices/dcinputmodel.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"

class DSCCreateInputModel : public IDCCreateInputModel
{
public:
    DCContext::IDCInputModel *createModel(const QByteArray &json, const IDCInputJsonKeys *jsonKeys) const override
    {
        return toModel(toJsonObject(json), jsonKeys);
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
    DCContext::IDCInputModel *toModel(const QJsonObject &obj, const IDCInputJsonKeys *jsonKeys) const
    {
        auto scoreModel = DCContext::DCInputModel::createInstance();
        scoreModel->setPlayerId(toId(obj.value(jsonKeys->playerId()).toString()));
        scoreModel->setPlayerName(obj.value(jsonKeys->playerName()).toString());
        scoreModel->setScore(obj.value(jsonKeys->score()).toInt());
        scoreModel->setTournamentId(toId(obj.value(jsonKeys->tournamentId()).toString()));
        return scoreModel;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
    }
    QUuid toId(const QString &stringId) const
    {
        return QUuid::fromString(stringId);
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
