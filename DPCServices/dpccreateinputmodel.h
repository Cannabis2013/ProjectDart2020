#ifndef DPCCREATEINPUTMODELS_H
#define DPCCREATEINPUTMODELS_H

#include <qjsonarray.h>
#include "dcinputmodel.h"
#include "idccreateinputmodel.h"


class DPCCreateInputModel : public IDCCreateInputModel
{
public:
    DCContext::IDCInputModel *createModel(const QByteArray &json, const IJsonValuesExtractor *extractor) const override
    {
        auto jsonObject = toJsonObject(json);
        return toModel(jsonObject,extractor);
    }
    virtual DCContext::IDCInputModel *createModel(const DCContext::DCScoreModel &scoreModel) const override
    {
        return toModel(scoreModel);
    }
private:
    DCContext::DCInputModel *toModel(const QJsonObject &jsonObject, const IJsonValuesExtractor *extractor) const
    {
        auto model = DCContext::DCInputModel::createInstance();
        model->setScore(extractor->toInt(jsonObject,"score"));
        model->setPoint(extractor->toInt(jsonObject,"point"));
        model->setModKeyCode(extractor->toInt(jsonObject,"modKeyCode"));
        model->setTotalScore(extractor->toInt(jsonObject,"totalScore"));
        model->setPlayerId(extractor->toId(jsonObject,"playerId"));
        model->setPlayerName(extractor->toString(jsonObject,"playerName"));
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
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
