#ifndef DARTSCONTROLLERPOINTBUILDER_H
#define DARTSCONTROLLERPOINTBUILDER_H

#include <qjsondocument.h>
#include <qjsonobject.h>
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
        const ModelsInterface *buildControllerPointByValues(const int &point,
                                                            const int &score,
                                                            const int &modKeyCode,
                                                            const IdFormat &playerId,
                                                            const StringFormat& playerName) const override
        {
            auto model = DartsControllerPoint::createInstance();
            model->setPoint(point);
            model->setAccumulatedScore(score);
            model->setModKeyCode(modKeyCode);
            model->setPlayerId(playerId);
            model->setPlayerName(playerName);
            return model;
        }
    };
}

#endif // DARTSCONTROLLERPOINTBUILDER_H
