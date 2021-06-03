#ifndef JSONARRAYFROMDARTSPOINTS_H
#define JSONARRAYFROMDARTSPOINTS_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "idartspointmodelsservice.h"
#include "idartspointinput.h"
#include "idartspointdb.h"

namespace DartsModelsContext{
    class AssembleJsonFromDartsPoints : public
            IUnaryService<const QVector<const IPlayerInput*>&,QByteArray>
    {
    public:
        typedef IDartsPointModelsService<IDartsPointDb> PointModelsService ;
        QByteArray service(const QVector<const IPlayerInput*>& models) override
        {
            QJsonArray pointsJsonArray;
            for (const auto& model : models) {
                auto dartsPoint = dynamic_cast<const IDartsPointInput*>(model);
                QJsonObject playerJsonObject;
                auto playerId = dartsPoint->playerId();
                playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
                playerJsonObject["point"] = dartsPoint->point();
                playerJsonObject["modKeyCode"] = dartsPoint->modKeyCode();
                pointsJsonArray << playerJsonObject;
            }
            auto json = QJsonDocument(pointsJsonArray).toJson();
            return json;
        }
    };
}


#endif // JSONARRAYFROMDARTSPOINTS_H
