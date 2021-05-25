#ifndef JSONARRAYFROMDARTSPOINTS_H
#define JSONARRAYFROMDARTSPOINTS_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "idartsmodelsservice.h"

namespace DartsModelsContext{
    class AssembleJsonFromDartsPoints : public
            IBinaryService<const QUuid&,const IDartsModelsService*,QByteArray>
    {
    public:
        QByteArray service(const QUuid& tournamentId,const IDartsModelsService* modelsService) override
        {
            auto dartsPlayerInputs = modelsService->dartsPointModelsByTournamentId(tournamentId);
            QJsonArray pointsJsonArray;
            for (const auto& dartsPlayerInput : dartsPlayerInputs) {
                auto dartsPoint = dynamic_cast<const IDartsPointInput*>(dartsPlayerInput);
                QJsonObject playerJsonObject;
                auto playerId = dartsPlayerInput->playerId();
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
