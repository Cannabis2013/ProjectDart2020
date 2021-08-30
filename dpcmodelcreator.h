#ifndef DARTSCONTROLLERPOINTBUILDER_H
#define DARTSCONTROLLERPOINTBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dpcmodel.h"
#include "idpcmodelcreator.h"

class DPCModelCreator : public IDPCModelCreator
{
public:
    DPCContext::IDPCModel *createModel(const QByteArray &json) const override
    {
        using namespace DPCContext;
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto point = jsonObject.value("point").toInt();
        auto score = jsonObject.value("score").toInt();
        auto totalScore = jsonObject.value("totalScore").toInt();
        auto modKeyCode = jsonObject.value("modKeyCode").toInt();
        auto playerId = QUuid::fromString(jsonObject.value("playerId").toString());
        auto playerName = jsonObject.value("playerName").toString();
        auto model = DPCModel::createInstance();
        model->setScore(score);
        model->setTotalScore(totalScore);
        model->setPoint(point);
        model->setModKeyCode(modKeyCode);
        model->setPlayerId(playerId);
        model->setTotalScore(0);
        return model;
    }
    QVector<DPCContext::IDPCModel*> createModels(const QByteArray &json) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto scoreData = document.array();
        QVector<DPCContext::IDPCModel*> dartsPointModels;
        for (const auto &jsonVal : scoreData) {
            auto newDocument = QJsonDocument(jsonVal.toObject());
            auto newJson = newDocument.toJson();
            auto dartsPointModel = createModel(newJson);
            dartsPointModels << dartsPointModel;
        }
        return dartsPointModels;
    }
    DPCContext::IDPCModel *createModel(const int &point, const int &score, const int &modKeyCode) const override
    {
        using namespace DPCContext;
        auto model = DPCModel::createInstance();
        model->setPoint(point);
        model->setScore(score);
        model->setModKeyCode(modKeyCode);
        return model;
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
