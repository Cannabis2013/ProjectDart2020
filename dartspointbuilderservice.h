#ifndef DARTSCONTROLLERPOINTBUILDER_H
#define DARTSCONTROLLERPOINTBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "iunaryservice.h"
#include "dartscontrollerpoint.h"
#include "idartscontrollerpointbuilder.h"

namespace DartsPointControllerContext
{
    typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
    class DartsPointBuilderService : public
            IDartsControllerpointBuilder<IControllerPoint,QByteArray,QUuid,QString>
    {
        // IDartsControllerpointBuilder interface
    public:
        const ModelsInterface *createPointModel(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto point = jsonObject.value("point").toInt();
            auto score = jsonObject.value("score").toInt();
            auto totalScore = jsonObject.value("totalScore").toInt();
            auto modKeyCode = jsonObject.value("modKeyCode").toInt();
            auto playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            auto playerName = jsonObject.value("playerName").toString();
            auto model = DartsControllerPoint::createInstance();
            model->setScore(score);
            model->setTotalScore(totalScore);
            model->setPoint(point);
            model->setModKeyCode(modKeyCode);
            model->setPlayerId(playerId);
            model->setTotalScore(0);
            return model;
        }
        QVector<const ModelsInterface *> createPointsByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto scoreData = document.array();
            QVector<const ModelsInterface*> dartsPointModels;
            for (const auto &jsonVal : scoreData) {
                auto newDocument = QJsonDocument(jsonVal.toObject());
                auto newJson = newDocument.toJson();
                auto dartsPointModel = createPointModel(newJson);
                dartsPointModels << dartsPointModel;
            }
            return dartsPointModels;
        }
        const ModelsInterface *createPointModel(const int &point,
                                                        const int &score,
                                                        const int &modKeyCode) const override
        {
            auto model = DartsControllerPoint::createInstance();
            model->setPoint(point);
            model->setScore(score);
            model->setModKeyCode(modKeyCode);
            return model;
        }

        const ModelsInterface *createPointModelWithTotalScoreByModel(const ModelsInterface* m,const int &totalScore) const override
        {
            auto model = DartsControllerPoint::createInstance();
            model->setPoint(m->point());
            model->setScore(m->score());
            model->setModKeyCode(m->modKeyCode());
            model->setTotalScore(totalScore);
            model->setPlayerId(m->playerId());
            return model;
        }
    };
}

#endif // DARTSCONTROLLERPOINTBUILDER_H
