#ifndef JSONARRAYFROMDARTSPOINTS_H
#define JSONARRAYFROMDARTSPOINTS_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include <idartspointinput.h>
#include "idartsmodelsservice.h"

class AssembleJsonFromDartsPoints : public
        IBinaryService<const QUuid&,const IDartsModelsService*,QByteArray>
{
public:
    QByteArray service(const QUuid& tournamentId,const IDartsModelsService*modelsService) override
    {
        auto scores = modelsService->dartsPointIds(tournamentId);
        QJsonArray scoresJsonArray;
        for (auto i = scores.constBegin(); i != scores.constEnd(); ++i) {
            auto scoreId = *i;
            QJsonObject playerJsonObject;
            auto playerId = modelsService->playerIdFromPointId(scoreId);
            playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
            playerJsonObject["point"] = modelsService->pointValueFromPointId(scoreId);
            playerJsonObject["modKeyCode"] = modelsService->pointKeyCode(scoreId);
            scoresJsonArray << playerJsonObject;
        }
        auto json = QJsonDocument(scoresJsonArray).toJson();
        return json;
    }
};

#endif // JSONARRAYFROMDARTSPOINTS_H
