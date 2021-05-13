#ifndef JSONARRAYFROMDARTSPOINTS_H
#define JSONARRAYFROMDARTSPOINTS_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "idartsmodelsservice.h"

class AssembleJsonFromDartsPoints : public
        IBinaryService<const QUuid&,const IDartsModelsService*,QByteArray>
{
public:
    QByteArray service(const QUuid& tournamentId,const IDartsModelsService*modelsService) override
    {
        auto dartsPointIds = modelsService->dartsPointIds(tournamentId);
        QJsonArray pointsJsonArray;
        for (const auto& dartsPointId : dartsPointIds) {
            QJsonObject playerJsonObject;
            auto playerId = modelsService->playerIdFromPointId(dartsPointId);
            playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
            playerJsonObject["point"] = modelsService->pointValueFromPointId(dartsPointId);
            playerJsonObject["modKeyCode"] = modelsService->pointKeyCode(dartsPointId);
            pointsJsonArray << playerJsonObject;
        }
        auto json = QJsonDocument(pointsJsonArray).toJson();
        return json;
    }
};

#endif // JSONARRAYFROMDARTSPOINTS_H
