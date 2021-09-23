#ifndef DCCREATEINPUTMODELS_H
#define DCCREATEINPUTMODELS_H

#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include "DartsController/DCScoresSLAs/idcscoresservice.h"
#include "DartsController/DCJsonSLAs/ijsonvaluesextractor.h"
#include "DartsController/DCInputServices/dcinputmodel.h"
#include <QJsonArray>
#include "DartsController/DCInputSLAs/idccreateinputmodel.h"
#include <qjsondocument.h>
#include "DartsController/DCInputSLAs/idccreateinputmodels.h"
#include "DartsController/DCInputSLAs/idcinputjsonkeys.h"

class DCCreateInputModels : public IDCCreateInputModels
{
public:
    QVector<DCContext::IDCInputModel*> createModels(const QByteArray &json, const IDCInputJsonKeys *jsonKeys,
                                                    const IDCCreateInputModel *modelBuilder) const override
    {
        QVector<DCContext::IDCInputModel*> dartsPointModels;
        for (const auto &jsonVal : toJsonArray(json))
            dartsPointModels << modelBuilder->createModel(toByteArray(jsonVal),jsonKeys);
        return dartsPointModels;
    }
    virtual QVector<DCContext::IDCInputModel *> createModels(IDCScoresService *scoresService,
                                                             const IDCCreateInputModel *modelBuilder) const override
    {
        QVector<DCContext::IDCInputModel*> models;
        for (const auto &scoreModel : scoresService->scoreModels())
            models << modelBuilder->createModel(scoreModel);
        return models;
    }
private:
    DCContext::DCInputModel *toModel(const DCContext::DCScoreModel &tuple) const
    {
        auto inputModel = DCContext::DCInputModel::createInstance();
        inputModel->setPlayerId(tuple.id);
        inputModel->setPlayerName(tuple.name);
        inputModel->setTotalScore(tuple.totalScore);
        return inputModel;
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.array();
    }
    QByteArray toByteArray(const QJsonValue &jsonValue) const
    {
        auto document = QJsonDocument(jsonValue.toObject());
        return document.toJson();
    }
};

#endif // DPCCREATEINPUTMODELS_H
