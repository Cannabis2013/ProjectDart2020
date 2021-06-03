#ifndef ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H
#define ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H

#include "iunaryservice.h"
#include "idartsmodelsservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

namespace DartsModelsContext {
    class AssembleJsonFromDartsMultiAttemptScores :
            public IUnaryService<const QVector<const IPlayerInput*>&,
                                 QByteArray>
    {
    public:
        QByteArray service(const QVector<const IPlayerInput*>& playerInputs) override
        {
            QJsonArray scoresJsonArray;
            for (const auto& playerInput : playerInputs) {
                auto dartsScoreInput = dynamic_cast<const IDartsScoreInput*>(playerInput);
                QJsonObject dartsScoreJsonObject;
                auto playerId = dartsScoreInput->playerId();
                dartsScoreJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
                dartsScoreJsonObject["score"] = dartsScoreInput->score();
                scoresJsonArray << dartsScoreJsonObject;
            }
            auto json = QJsonDocument(scoresJsonArray).toJson();
            return json;
        }
    };
}


#endif // ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H
