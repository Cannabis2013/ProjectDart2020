#ifndef DARTSCONTROLLERPOINTBUILDER_H
#define DARTSCONTROLLERPOINTBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "iunaryservice.h"
#include "dartscontrollerpoint.h"
#include "idartscontrollerpointbuilder.h"

namespace DartsPointSingleAttemptContext
{
    typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
    class DartsControllerPointBuilder : public IDartsControllerpointBuilder<IControllerPoint,QByteArray,QUuid,QString>
    {
        // IDartsControllerpointBuilder interface
    public:
        const ModelsInterface *buildControllerPointByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto jsonObject = document.object();
            auto point = jsonObject.value("point").toInt();
            auto modKeyCode = jsonObject.value("modKeyCode").toInt();
            auto playerId = QUuid::fromString(jsonObject.value("playerId").toString());
            auto playerName = jsonObject.value("playerName").toString();
            auto model = DartsControllerPoint::createInstance();
            model->setPoint(point);
            model->setModKeyCode(modKeyCode);
            model->setPlayerId(playerId);
            model->setPlayerName(playerName);
            model->setAccumulatedScore(0);
            return model;
        }
        const ModelsInterface *buildControllerPointByInputValues(const int &point,
                                                            const int &score,
                                                            const int &modKeyCode) const override
        {
            auto model = DartsControllerPoint::createInstance();
            model->setPoint(point);
            model->setAccumulatedScore(score);
            model->setModKeyCode(modKeyCode);
            return model;
        }

        QVector<const ModelsInterface *> buildControllerPointsByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto scoreData = document.array();
            QVector<const ModelsInterface*> dartsPointModels;
            for (const auto &jsonVal : scoreData) {
                auto newDocument = QJsonDocument(jsonVal.toObject());
                auto newJson = newDocument.toJson();
                auto dartsPointModel = buildControllerPointByJson(newJson);
                dartsPointModels << dartsPointModel;
            }
            return dartsPointModels;
        }
    };
}

#endif // DARTSCONTROLLERPOINTBUILDER_H
