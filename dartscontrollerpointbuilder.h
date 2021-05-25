#ifndef DARTSCONTROLLERPOINTBUILDER_H
#define DARTSCONTROLLERPOINTBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include "iunaryservice.h"
#include "dartscontrollerpoint.h"

namespace DartsPointSingleAttemptContext
{
    typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
    typedef IUnaryService<const QByteArray&, const IControllerPoint*> IControllerPointBuilder;
    class DartsControllerPointBuilder : public IControllerPointBuilder
    {
    public:

        // IUnaryService interface
    public:
        const IControllerPoint* service(const QByteArray& json) override
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
    };
}

#endif // DARTSCONTROLLERPOINTBUILDER_H
