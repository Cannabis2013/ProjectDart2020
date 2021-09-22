#ifndef DCCREATEINPUTMODELS_H
#define DCCREATEINPUTMODELS_H

#include "DCInputsSLA/idcinputmodel.h"
#include "idcscoresservice.h"
#include "ijsonvaluesextractor.h"
#include "dcinputmodel.h"
#include <QJsonArray>
#include <idccreateinputmodel.h>
#include <qjsondocument.h>
#include "DCInputsSLA/idcreateinputmodels.h"

class DCCreateInputModels : public IDCCreateInputModels
{
public:
    QVector<DCContext::IDCInputModel*> createModels(const QByteArray &json, const IJsonValuesExtractor *extractor,
                                                    const IDCCreateInputModel *modelBuilder) const override
    {
        QVector<DCContext::IDCInputModel*> dartsPointModels;
        for (const auto &jsonVal : toJsonArray(json))
            dartsPointModels << modelBuilder->createModel(toByteArray(jsonVal),extractor);
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
