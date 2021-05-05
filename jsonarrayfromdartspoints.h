#ifndef JSONARRAYFROMDARTSPOINTS_H
#define JSONARRAYFROMDARTSPOINTS_H

#include "ibinaryservice.h"
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include <idartspointinput.h>
#include "idartsmodelsservice.h"

class JsonArrayFromDartsPoints : public
        IBinaryService<const QUuid&,const IDartsModelsService*,QJsonArray>
{
public:
    QJsonArray service(const QUuid& tournamentId,const IDartsModelsService*modelsService) override
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
        return scoresJsonArray;
    }
};

#endif // JSONARRAYFROMDARTSPOINTS_H
