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
        auto dartsPointModels = modelsService->dartsPointModelsByTournamentId(tournamentId);
        QJsonArray pointsJsonArray;
        for (const auto& dartsPointModel : dartsPointModels) {
            QJsonObject playerJsonObject;
            auto playerId = dartsPointModel->playerId();
            playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
            playerJsonObject["point"] = dartsPointModel->point();
            playerJsonObject["modKeyCode"] = dartsPointModel->modKeyCode();
            pointsJsonArray << playerJsonObject;
        }
        auto json = QJsonDocument(pointsJsonArray).toJson();
        return json;
    }
};

#endif // JSONARRAYFROMDARTSPOINTS_H
