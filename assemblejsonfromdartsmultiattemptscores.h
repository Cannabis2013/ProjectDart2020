#ifndef ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H
#define ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H

#include "iunaryservice.h"
#include "idartsmodelsservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>


class AssembleJsonFromDartsMultiAttemptScores :
        public IUnaryService<const QVector<const IDartsScoreInput*>&,
                             QByteArray>
{
public:
    QByteArray service(const QVector<const IDartsScoreInput*>& models) override
    {
        QJsonArray scoresJsonArray;
        for (const auto& model : models) {
            QJsonObject dartsScoreJsonObject;
            auto playerId = model->playerId();
            dartsScoreJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
            dartsScoreJsonObject["score"] = model->score();
            scoresJsonArray << dartsScoreJsonObject;
        }
        auto json = QJsonDocument(scoresJsonArray).toJson();
        return json;
    }
};

#endif // ASSEMBLEJSONFROMDARTSMULTIATTEMPTSCORES_H
