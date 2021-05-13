#ifndef ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H
#define ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H

#include "ibinaryservice.h"
#include "idartsmodelsservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>


class AssembleJsonFromDartsMultiAttemptScores :
        public IBinaryService<const QUuid&,
                       const IDartsModelsService*,
                       QByteArray>
{
public:
    QByteArray service(const QUuid& tournamentId,const IDartsModelsService* modelsService) override
    {
        auto dartsScoreIds = modelsService->dartsScoreIds(tournamentId);
        QJsonArray scoresJsonArray;
        for (const auto& dartsScoreId : dartsScoreIds) {
            QJsonObject dartsScoreJsonObject;
            auto playerId = modelsService->playerIdFromScoreId(dartsScoreId);
            dartsScoreJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
            dartsScoreJsonObject["score"] = modelsService->ScoreValueFromScoreId(dartsScoreId);
            scoresJsonArray << dartsScoreJsonObject;
        }
        auto json = QJsonDocument(scoresJsonArray).toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H
