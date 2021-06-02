#ifndef JSONARRAYFROMDARTSPOINTS_H
#define JSONARRAYFROMDARTSPOINTS_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include "idartspointmodelsservice.h"
#include "idartspointinput.h"

namespace DartsModelsContext{
    class AssembleJsonFromDartsPoints : public
            IBinaryService<const QUuid&,const IDartsPointModelsService*,QByteArray>
    {
    public:
        QByteArray service(const QUuid& tournamentId,const IDartsPointModelsService* modelsService) override
        {
            auto dartsPlayerInputs = modelsService->dartsPointModelsByTournamentId(tournamentId);
            QJsonArray pointsJsonArray;
            for (const auto& dartsPlayerInput : dartsPlayerInputs) {
                auto dartsPoint = dynamic_cast<const IDartsPointInput*>(dartsPlayerInput);
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
