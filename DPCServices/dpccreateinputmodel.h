#ifndef DPCCREATEINPUTMODELS_H
#define DPCCREATEINPUTMODELS_H

#include <qjsonarray.h>
#include "DCInputServices/dcinputmodel.h"
#include "DCInputSLAs/idccreateinputmodel.h"


class DPCCreateInputModel : public IDCCreateInputModel
{
public:
    DCContext::IDCInputModel *createModel(const QByteArray &json, const IDCInputJsonKeys *jsonKeys) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject,jsonKeys);
    }
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const override
    {
        return toModel(scoreModel);
    }
private:
    DCContext::DCInputModel *toModel(const QJsonObject &jsonObject, const IDCInputJsonKeys *jsonKeys) const
    {
        auto model = DCContext::DCInputModel::createInstance();
        model->setScore(jsonObject.value(jsonKeys->score()).toInt());
        model->setPoint(jsonObject.value(jsonKeys->point()).toInt());
        model->setModKeyCode(jsonObject.value(jsonKeys->modKeyCode()).toInt());
        model->setTotalScore(jsonObject.value(jsonKeys->totalScore()).toInt());
        model->setPlayerId(toId(jsonObject.value(jsonKeys->playerId()).toString()));
        model->setPlayerName(jsonObject.value(jsonKeys->playerName()).toString());
        model->setTotalScore(0);
        return model;
    }
    DCContext::DCInputModel *toModel(const DCContext::DCScoreModel &tuple) const
    {
        auto inputModel = DCContext::DCInputModel::createInstance();
        inputModel->setPlayerId(tuple.id);
        inputModel->setPlayerName(tuple.name);
        inputModel->setTotalScore(tuple.totalScore);
        return inputModel;
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
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
